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

	PostingStream *ps = is.fileIndex->fetchPostingStream(fieldID, term);
	if ( ps == NULL ) return vector<ScoreDoc>();

	vector<ScoreDoc> res = ps->getScoreDocs(is);
	delete ps;

	return res;
}

/** the result need to be deleted. **/
PostingStream* TermQuery::fetchPostingStream(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	return is.fileIndex->fetchPostingStream(fieldID, term);
}


