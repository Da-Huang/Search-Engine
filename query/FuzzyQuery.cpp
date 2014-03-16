#include <util.h>
#include <FuzzyQuery.h>
#include <algorithm>
#include <queue>
#include <TmpPostingStream.h>
#include <GreaterPostingStream.h>
#include <GreaterPos.h>


vector<ScoreDoc> FuzzyQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> res;

	vector<PostingStream*> psv = fetchPostingStreams(is);
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
	vector<PostingStream*> psv = fetchPostingStreams(is);
	priority_queue<PostingStream*, vector<PostingStream*>, 
		GreaterPostingStream> pq;
	for (size_t i = 0; i < psv.size(); i ++) pq.push(psv[i]);

	PostingStream *res = new TmpPostingStream();
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
		for (size_t i = 0; i < pv.size(); i ++) pqPos.push(i);

		Posting mergedPosting(docID);
		while ( !pqPos.empty() ) {
			size_t i = pqPos.top();
			pqPos.pop();
			mergedPosting.addPos(pv[i].posList[index[i] ++]);
			if ( index[i] < pv[i].posList.size() ) pqPos.push(i);
		}
		((TmpPostingStream*)res)->write(mergedPosting);
	}
//	cout << res->info() << endl;
	return res;
}

vector<PostingStream*> FuzzyQuery::fetchPostingStreams(
		IndexSearcher &is) const {

	vector<PostingStream*> res;

	size_t prefixSize = min(term.length(), size_t(2));
	string firstTerm = term.substr(0, prefixSize);
	size_t first = is.fileIndex->findGETermID(firstTerm);
	string lastTerm = firstTerm;
	lastTerm[lastTerm.length() - 1] ++;
//	cout << "l:" << lastTerm << endl;
	size_t last = is.fileIndex->findLTTermID(lastTerm);

	size_t fieldID = is.fieldNameMap->getFieldID(field);
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


