#include <queue>
#include <cmath>
#include <algorithm>
#include <util.h>
#include <FuzzyQuery.h>
#include <TmpPostingStream.h>
#include <GreaterPos.h>
#include <GreaterPostingStream.h>


vector<ScoreDoc> FuzzyQuery::search(IndexSearcher &is) const {
	const size_t fieldID = is.fieldNameMap->getFieldID(field);
	PostingStream *ps = fetchPostingStream(is, fieldID);
	vector<ScoreDoc> res = ps->getScoreDocs(is, fieldID);
	delete ps;
	return res;
}

PostingStream* FuzzyQuery::fetchPostingStream(IndexSearcher &is) const {
	const size_t fieldID = is.fieldNameMap->getFieldID(field);
	return fetchPostingStream(is, fieldID);
}

PostingStream* FuzzyQuery::fetchPostingStream(
		IndexSearcher &is, size_t fieldID) const {

	map<PostingStream*, double> boosts;
	vector<PostingStream*> psv = fetchPostingStreams(is, fieldID, boosts);

	PostingStream *res = new TmpPostingStream();
	res->writeMerge(psv, &is, fieldID, boosts);
	res->rewind();
	return res;
}

vector<PostingStream*> FuzzyQuery::fetchPostingStreams(
		IndexSearcher &is, size_t fieldID, 
		map<PostingStream*, double> &boosts) const {

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
		size_t edis;
		if ( util::delta(term.length(), this->term.length()) > dis ||
			(edis = util::editDistance(this->term, term)) > dis ) continue;
//		cout << term << endl;
		PostingStream* ps = is.fileIndex->fetchPostingStream(fieldID, i);
		if ( ps != NULL && ps->hasNext() ) {
			res.push_back(ps);
			boosts[ps] = 1 / exp(double(edis));
		}
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


