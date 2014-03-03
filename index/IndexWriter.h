#ifndef _INDEX_WRITER_H_
#define _INDEX_WRITER_H_

#include <string>
#include <Document.h>
#include <Dictionary.h>
#include <MMIndex.h>

using namespace std;

class IndexWriter {
private:
	const string &dirPath;
	MMIndex mmIndex;
public:
	IndexWriter(const string &dirPath);
	virtual void write(Document &doc);
	virtual void close();
	virtual void merge();
	virtual ~IndexWriter() {}
};

#endif
