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
	FieldNameMap *fieldNameMap;
	ofstream trmOut;
	ofstream idxOut;
	ofstream pstOut;

public:
	IndexMerger(const string &path);
	virtual void merge();
	virtual void close();
	virtual ~IndexMerger();
};


#endif
