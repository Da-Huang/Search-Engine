#ifndef _INDEX_WRITER_H_
#define _INDEX_WRITER_H_

#include <map>
#include <string>
#include <fstream>
#include <Document.h>
#include <Dictionary.h>
#include <MMIndex.h>
#include <FieldNameMap.h>

using namespace std;

class IndexWriter {
private:
	const string dirPath;
	MMIndex mmIndex;
	size_t currentDocID;
	ofstream docOut;
	ofstream cntOut;

	FieldNameMap fieldNameMap;
	
public:
	IndexWriter(const string &dirPath);
	void addFieldName(const string &fieldName);
	virtual void write(Document &doc);
	virtual void close();
	virtual void merge();
	virtual ~IndexWriter() {}
};

#endif
