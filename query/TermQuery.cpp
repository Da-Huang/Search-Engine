#include <TermQuery.h>
#include <PostingStream.h>


vector<ScoreDoc> TermQuery::search(IndexSearcher &is) const {
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	return is.fileIndex->search(fieldID, term);
}


