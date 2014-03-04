#ifndef _INDEX_SEARCHER_H_
#define _INDEX_SEARCHER_H_

#include <vector>
#include <TopDoc.h>
#include <FileIndex.h>
#include <DocDB.h>
#include <FieldNameMap.h>
#include <Query.h>

class IndexSearcher {
private:
	FileIndex *fileIndex;
	DocDB *docDB;
public:
	IndexSearcher(const string &prefix);
	virtual TopDoc search(const Query &query);
	virtual Document doc(const ScoreDoc &scoreDoc);
	virtual ~IndexSearcher();
};

#endif
