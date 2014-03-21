#ifndef _INDEX_WRITER_H_
#define _INDEX_WRITER_H_

#include <map>
#include <string>
#include <fstream>
#include <Document.h>
#include <MMIndex.h>
#include <FieldNameMap.h>

using namespace std;

class IndexWriter {
private:
	const string dirPath;
	MMIndex mmIndex;
	size_t currentDocID;
	size_t currentSegID;
	ofstream docOut;
	ofstream cntOut;

	FieldNameMap fieldNameMap;
	
protected:
	virtual void saveSegment();
public:
	IndexWriter(const string &dirPath);
	virtual void addFieldName(const string &fieldName);
	virtual void write(Document &doc);
	virtual void close();
	virtual void merge();
	virtual string toString() const;
	virtual ~IndexWriter() {}
};

#endif
