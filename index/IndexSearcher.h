#ifndef _INDEX_SEARCHER_H_
#define _INDEX_SEARCHER_H_

#include <vector>
#include <DocDB.h>
#include <ScoreDoc.h>
#include <FileIndex.h>
#include <FieldNameMap.h>

class Query;

class IndexSearcher {
private:
	FileIndex *fileIndex;
	DocDB *docDB;
	FieldNameMap *fieldNameMap;
public:
	IndexSearcher(const string &prefix);
	virtual vector<ScoreDoc> search(const Query &query);
	virtual Document doc(const ScoreDoc &scoreDoc);
	virtual string toString();
	virtual ~IndexSearcher();

	friend class TermQuery;
	friend class NotQuery;
	friend class PhraseQuery;
};

#endif
