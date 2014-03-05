#include <TermQuery.h>
#include <PostingStream.h>


string TermQuery::toString() const {
	string res;
	res += field;
	res += ":";
	res += term;
	return res;
}

vector<ScoreDoc> TermQuery::search(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	return is.fileIndex->search(fieldID, term);
}


