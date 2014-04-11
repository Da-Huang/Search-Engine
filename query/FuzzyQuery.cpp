#include <queue>
#include <cmath>
#include <algorithm>
#include <BM25.h>
#include <util.h>
#include <FuzzyQuery.h>
#include <TmpPostingStream.h>
#include <GreaterPos.h>
#include <GreaterPostingStream.h>


vector<ScoreDoc> FuzzyQuery::search(IndexSearcher &is) const {
	const size_t fieldID = is.fieldNameMap->getFieldID(field);
	PostingStream *ps = fetchPostingStream(is, fieldID);
	vector<ScoreDoc> res = ps->getScoreDocs(is, fieldID);
	for (size_t i = 0; i < res.size(); i ++) res[i] *= boost;
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

	size_t first, last;
	tie(first, last) = fetchScope(is, fieldID);
	if ( first == 0 || first > is.fileIndex->getTermNum() ) return res;
	if (  last == 0 ||  last > is.fileIndex->getTermNum() ) return res;

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

tuple<size_t, size_t> FuzzyQuery::fetchScope(
		IndexSearcher &is, size_t fieldID) const {
	size_t prefixSize = min(term.length(), size_t(2));
	string firstTerm = term.substr(0, prefixSize);
	size_t first = is.fileIndex->findGETermID(firstTerm);
	string lastTerm = firstTerm;
	lastTerm[lastTerm.length() - 1] ++;
	size_t last = is.fileIndex->findLTTermID(lastTerm);
	return make_tuple(first, last);
}

map<string, double> FuzzyQuery::fetchScoreTerms(IndexSearcher &is) const {
	const size_t fieldID = is.fieldNameMap->getFieldID(field);
	return fetchScoreTerms(is, fieldID);
}

map<string, double> FuzzyQuery::fetchScoreTerms(
		IndexSearcher &is, size_t fieldID) const {

	map<string, double> res;
	size_t first, last;
	tie(first, last) = fetchScope(is, fieldID);
	if ( first == 0 || first > is.fileIndex->getTermNum() ) return res;
	if (  last == 0 ||  last > is.fileIndex->getTermNum() ) return res;

	for (size_t i = first; i <= last; i ++) {
		string term = is.fileIndex->fetchTerm(i);
//		cout << term << endl;
		size_t edis;
		if ( util::delta(term.length(), this->term.length()) > dis ||
			(edis = util::editDistance(this->term, term)) > dis ) continue;
//		cout << term << endl;
		auto info = is.fileIndex->getPostingListInfo(i, fieldID);
		size_t df = get<1>(info);
		res[term] = BM25::idf(df, is.docDB->getDocNum()) /
					exp(double(edis));
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


