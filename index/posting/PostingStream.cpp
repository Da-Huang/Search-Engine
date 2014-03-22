#include <queue>
#include <PostingStream.h>
#include <GreaterPos.h>
#include <GreaterPostingStream.h>


PostingStream::PostingStream(istream &in, size_t begin, size_t end)
	: in(in), out(cout), begin(begin), end(end), current(begin) {
	in.seekg(end);
	size_t skipsNum;
	in.read((char*)&skipsNum, sizeof(skipsNum));
	for (size_t i = 0; i < skipsNum; i ++) {
		skips.push_back(SkipEntry(in));
	}
}

Posting	PostingStream::next() {
	in.seekg(current);
	size_t docID;
	in.read((char*)&docID, sizeof(docID));
	Posting res(docID);

	size_t posListSize;
	in.read((char*)&posListSize, sizeof(posListSize));
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos;
		in.read((char*)&pos, sizeof(pos));
		res.addPos(pos);
	}
	current = in.tellg();
	return res;
}

Posting PostingStream::peek() {
	size_t current = this->current;
	Posting posting = next();
	this->current = current;
	return posting;
}

size_t PostingStream::nextDocID() {
	in.seekg(current);
	size_t docID;
	in.read((char*)&docID, sizeof(docID));
	size_t posListSize;
	in.read((char*)&posListSize, sizeof(posListSize));
	in.seekg(posListSize * sizeof(size_t), ios::cur);
	current = in.tellg();
	return docID;
}

size_t PostingStream::peekDocID() {
	in.seekg(current);
	size_t docID;
	in.read((char*)&docID, sizeof(docID));
	return docID;
}

string PostingStream::toString() {
	size_t oldCurrent = current;
	current = begin;
	string res = "[";
	while ( hasNext() ) {
		res += next().toString();
//		res += to_string(nextDocID());
		res += ";";
	}
	current = oldCurrent;
	if ( res[res.length() - 1] == ';' ) res.erase(res.length() - 1);
	res += "]";
	return res;
}	

string PostingStream::info() {
	size_t oldCurrent = current;
	current = begin;
	string res = "[";
	while ( hasNext() ) {
		Posting posting = next();
		res += to_string(posting.getDocID());
		res += ":";
		res += to_string(posting.size() - sizeof(posting.getDocID()));
		res += ";";
	}
	current = oldCurrent;
	if ( res[res.length() - 1] == ';' ) res.erase(res.length() - 1);
	res += "]";
	return res;
}

void PostingStream::write(const Posting &posting) {
	posting.writeTo(out);
	end = out.tellp();
}

void PostingStream::writeSkips() {
	size_t size = skips.size();
	out.write((char*)&size, sizeof(size));
	for (size_t i = 0; i < skips.size(); i ++) skips[i].writeTo(out);
}

/** elements in psv would be deleted **/
void PostingStream::writeMerge(vector<PostingStream*> &psv) {
	priority_queue<PostingStream*, vector<PostingStream*>, 
		GreaterPostingStream> pq;
	for (size_t i = 0; i < psv.size(); i ++) pq.push(psv[i]);

	while ( !pq.empty() ) {
		PostingStream *ps = pq.top();
		pq.pop();

		vector<Posting> pv;
		pv.push_back(ps->next());
		size_t docID = pv[0].docID;
		if ( ps->hasNext() ) pq.push(ps);
		else delete ps;

		while ( !pq.empty() && pq.top()->peekDocID() == docID ) {
			ps = pq.top();
			pq.pop();
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
		write(mergedPosting);
	}
//	end = out.tellg();
//	cout << info() << endl;
}


