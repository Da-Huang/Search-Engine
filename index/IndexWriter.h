#ifndef _INDEX_WRITER_H_
#define _INDEX_WRITER_H_

#include <map>
#include <string>
#include <Document.h>
#include <Dictionary.h>
#include <MMIndex.h>

using namespace std;

class IndexWriter {
private:
	const string &dirPath;
	MMIndex mmIndex;
	size_t currentDocID;

	map<string, size_t> fieldIDMap;
	vector<string> fields;
	
public:
	IndexWriter(const string &dirPath);
	void addField(const string &field);
	virtual void write(Document &doc);
	virtual void close();
	virtual void merge();
	virtual ~IndexWriter() {}
};

#endif
