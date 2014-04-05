#include <util.h>
#include <FuzzyQuery.h>
#include <algorithm>
#include <queue>
#include <TmpPostingStream.h>
#include <GreaterPostingStream.h>
#include <GreaterPos.h>


vector<ScoreDoc> FuzzyQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> res;

	size_t fieldID = is.fieldNameMap->getFieldID(field);
	vector<PostingStream*> psv = fetchPostingStreams(is, fieldID);
	priority_queue<PostingStream*, vector<PostingStream*>, 
		GreaterPostingStream> pq;
	for (size_t i = 0; i < psv.size(); i ++) pq.push(psv[i]);

	while ( !pq.empty() ) {
		PostingStream *ps = pq.top();
		pq.pop();
		size_t docID = ps->nextDocID();
		if ( ps->hasNext() ) pq.push(ps);
		else delete ps;

//		cout << docID << endl;
		while ( !pq.empty() && pq.top()->peekDocID() == docID ) {
			ps = pq.top();
			pq.pop();
			ps->nextDocID();
			if ( ps->hasNext() ) pq.push(ps);
			else delete ps;
		}

		res.push_back(ScoreDoc(docID));
	}
//	cout << "------------" << endl;
	return res;
}

PostingStream* FuzzyQuery::fetchPostingStream(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	return fetchPostingStream(is, fieldID);
}

PostingStream* FuzzyQuery::fetchPostingStream(
		IndexSearcher &is, size_t fieldID) const {
	vector<PostingStream*> psv = fetchPostingStreams(is, fieldID);
	PostingStream *res = new TmpPostingStream();
	res->writeMerge(psv);
	res->rewind();
//	cout << res->toString() << endl;
	return res;
}

vector<PostingStream*> FuzzyQuery::fetchPostingStreams(
		IndexSearcher &is, size_t fieldID) const {

	vector<PostingStream*> res;

	size_t prefixSize = min(term.length(), size_t(2));
	string firstTerm = term.substr(0, prefixSize);
	size_t first = is.fileIndex->findGETermID(firstTerm);
	string lastTerm = firstTerm;
	lastTerm[lastTerm.length() - 1] ++;
//	cout << "l:" << lastTerm << endl;
	size_t last = is.fileIndex->findLTTermID(lastTerm);

	for (size_t i = first; i <= last; i ++) {
		string term = is.fileIndex->fetchTerm(i);
//		cout << term << endl;
		if ( util::delta(term.length(), this->term.length()) > dis ||
			util::editDistance(this->term, term) > dis ) continue;
//		cout << term << endl;
		PostingStream* ps = is.fileIndex->fetchPostingStream(fieldID, i);
		if ( ps != NULL && ps->hasNext() ) res.push_back(ps);
//		cout << ps->info() << endl;
	}
	return res;
}

string FuzzyQuery::toString() const {
	string res;
	res += field;
	res += ":f";
	res += to_string(dis);
	res += "\"";
	res += term;
	res += "\"";
	return res;
}


