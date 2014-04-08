#include <queue>
#include <util.h>
#include <BM25.h>
#include <cassert>
#include <IndexSearcher.h>
#include <PostingStream.h>
#include <GreaterPos.h>
#include <GreaterPostingStream.h>


PostingStream::PostingStream(
		istream &in, size_t begin, size_t df, size_t end)
	: in(in), out(cout), begin(begin), end(end), current(begin), 
		baseDocID(0), df(df) {

	in.seekg(end);
	size_t skipsNum = util::codec.decode(in);
	// TODO: Skipping list may need delta codec.
	for (size_t i = 0; i < skipsNum; i ++) {
		skips.push_back(SkipEntry(in));
	}
}

void PostingStream::rewind() {
	current = begin;
	baseDocID = 0;
}

Posting	PostingStream::next() {
	in.seekg(current);
	Posting res(in, baseDocID);
	baseDocID = res.getDocID();
	current = in.tellg();
	return res;
}

Posting PostingStream::peek() {
	return Posting(in, baseDocID);
}

size_t PostingStream::nextDocID() {
	in.seekg(current);
	size_t docID = util::codec.decode(in) + 
			(util::codec.isDelta() ? baseDocID : 0);
	baseDocID = docID;
	/*size_t tf =*/ util::codec.decode(in);
	size_t plBytes = util::codec.decode(in);
//	cerr << "ps: pl= " << plBytes << endl;
	in.seekg(plBytes, ios::cur);
	current = in.tellg();
	return docID;
}

tuple<size_t, size_t> PostingStream::nextDocIDTF() {
	in.seekg(current);
	size_t docID = util::codec.decode(in) + 
			(util::codec.isDelta() ? baseDocID : 0);
	baseDocID = docID;
	size_t tf = util::codec.decode(in);
	size_t plBytes = util::codec.decode(in);
	in.seekg(plBytes, ios::cur);
	current = in.tellg();
	return make_tuple(docID, tf);
}

double PostingStream::peekScore(IndexSearcher &is, size_t fieldID) {
	in.seekg(current);
	size_t docID = util::codec.decode(in) + 
			(util::codec.isDelta() ? baseDocID : 0);
	size_t DOC_NUM = is.docDB->getDocNum();
	size_t tf = util::codec.decode(in);
	size_t dl = is.docDB->getDocFieldDL(docID, fieldID);
	double avgdl = is.fieldNameMap->getAvgdl(fieldID);
	return BM25::score(df, DOC_NUM, tf, dl , avgdl);
}

size_t PostingStream::peekDocID() {
	in.seekg(current);
	size_t docID = util::codec.decode(in) + 
			(util::codec.isDelta() ? baseDocID : 0);
	return docID;
}

string PostingStream::toString() {
	size_t current = this->current;
	size_t baseDocID = this->baseDocID;
	this->current = begin;
	this->baseDocID = 0;
	string res = "[";
	while ( hasNext() ) {
		res += next().toString();
//		res += to_string(nextDocID());
		res += ";";
	}
	this->current = current;
	this->baseDocID = baseDocID;
	if ( res[res.length() - 1] == ';' ) res.erase(res.length() - 1);
	res += "]";
	return res;
}	

string PostingStream::info() {
	size_t current = this->current;
	size_t baseDocID = this->baseDocID;
	this->current = begin;
	this->baseDocID = 0;
	string res = "[";
	while ( hasNext() ) {
		Posting posting = next();
		res += to_string(posting.getDocID());
		res += ":";
		res += to_string(posting.size() - sizeof(posting.getDocID()));
		res += ";";
	}
	this->current = current;
	this->baseDocID = baseDocID;
	if ( res[res.length() - 1] == ';' ) res.erase(res.length() - 1);
	res += "]";
	return res;
}

void PostingStream::write(const Posting &posting, double score) {
	assert (score == 0);
	posting.writeTo(out, baseDocID);
	baseDocID = posting.getDocID();
	end = out.tellp();
	df ++;
}

void PostingStream::writeSkips() {
	size_t size = skips.size();
	util::codec.encode(out, size);
	for (size_t i = 0; i < skips.size(); i ++) skips[i].writeTo(out);
}

/** elements in psv would be deleted **/
void PostingStream::writeMerge(vector<PostingStream*> &psv, 
		IndexSearcher *is, size_t fieldID, 
		map<PostingStream*, double> boosts) {

	assert (is == NULL || psv.size() == boosts.size());

	priority_queue<PostingStream*, vector<PostingStream*>, 
		GreaterPostingStream> pq;
	for (size_t i = 0; i < psv.size(); i ++) pq.push(psv[i]);

	while ( !pq.empty() ) {
		PostingStream *ps = pq.top();
		pq.pop();

		double score = 0;
		vector<Posting> pv;
		if ( is ) score += ps->peekScore(*is, fieldID) * boosts[ps];
		pv.push_back(ps->next());
		size_t docID = pv[0].docID;
		if ( ps->hasNext() ) pq.push(ps);
		else delete ps;

		while ( !pq.empty() && pq.top()->peekDocID() == docID ) {
			ps = pq.top();
			pq.pop();
			if ( is ) score += ps->peekScore(*is, fieldID) * boosts[ps];
			pv.push_back(ps->next());
			if ( ps->hasNext() ) pq.push(ps);
			else delete ps;
		}

		vector<size_t> index(pv.size(), 0);
		GreaterPos greaterPos(pv, index);
		priority_queue<size_t, vector<size_t>, GreaterPos>
			pqPos(greaterPos);
		for (size_t i = 0; i < pv.size(); i ++) {
			if ( index[i] < pv[i].posList.size() ) pqPos.push(i);
		}

		Posting mergedPosting(docID);
		while ( !pqPos.empty() ) {
			size_t i = pqPos.top();
			pqPos.pop();
			mergedPosting.addPos(pv[i].posList[index[i] ++]);
			if ( index[i] < pv[i].posList.size() ) pqPos.push(i);
		}
		// This is a polymorphic write.
		write(mergedPosting, score);
	}
//	cout << info() << endl;
}

PostingStream::~PostingStream() {}

vector<ScoreDoc> PostingStream::getScoreDocs(
		IndexSearcher &is, size_t fieldID) {

	size_t current = this->current;
	size_t baseDocID = this->baseDocID;
	this->current = begin;
	this->baseDocID = 0;

	vector<ScoreDoc> res;
	while ( hasNext() ) {
		double score = peekScore(is, fieldID);
		size_t docID = nextDocID();
		res.push_back(ScoreDoc(docID, score));
	}

	this->current = current;
	this->baseDocID = baseDocID;
	return res;
}


