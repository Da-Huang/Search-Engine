#include <BM25.h>
#include <TermQuery.h>
#include <PostingStream.h>


vector<ScoreDoc> TermQuery::search(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	PostingStream *ps = fetchPostingStream(is, fieldID);
	if ( ps == NULL ) return vector<ScoreDoc>();

	vector<ScoreDoc> res = ps->getScoreDocs(is, fieldID);
	delete ps;
	return res;
}

/** the result need to be deleted. **/
PostingStream* TermQuery::fetchPostingStream(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	return fetchPostingStream(is, fieldID);
}

/** the result need to be deleted. **/
PostingStream* TermQuery::fetchPostingStream(
		IndexSearcher &is, size_t fieldID) const {
	return is.fileIndex->fetchPostingStream(fieldID, term);
}

map<string, double> TermQuery::fetchScoreTerms(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	return fetchScoreTerms(is, fieldID);
}

map<string, double> TermQuery::fetchScoreTerms(
		IndexSearcher &is, size_t fieldID) const {
	map<string, double> res;
	size_t termID = is.fileIndex->findTermID(term);
	if ( termID == 0 ) return res;
	auto info = is.fileIndex->getPostingListInfo(termID, fieldID);
	size_t df = get<1>(info);
	res[term] = BM25::idf(df, is.docDB->getDocNum());
	return res;
}

string TermQuery::toString() const {
	string res;
	res += field;
	res += ":\"";
	res += term;
	res += "\"";
	return res;
}


