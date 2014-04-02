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
	const FieldNameMap &fieldNameMap;
	ofstream trmOut;
	ofstream idxOut;
	ofstream pstOut;

public:
	IndexMerger(const string &path, const FieldNameMap &fieldNameMap);
	virtual void merge();
	virtual void close();
	virtual ~IndexMerger();
};


#endif
