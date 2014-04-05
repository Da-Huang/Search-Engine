#include <TermQuery.h>
#include <PostingStream.h>


string TermQuery::toString() const {
	string res;
	res += field;
	res += ":\"";
	res += term;
	res += "\"";
	return res;
}

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


