#ifndef _INDEX_MERGER_H_
#define _INDEX_MERGER_H_

#include <FileIndex.h>
#include <DocDB.h>
#include <FieldNameMap.h>
#include <vector>

using namespace std;


class IndexMerger {
private:
	vector<FileIndex*> fileIndexes;
	DocDB *docDB;
	FieldNameMap *fieldNameMap;
public:
	IndexMerger(const string &path);
	virtual ~IndexMerger() {}
};


#endif
