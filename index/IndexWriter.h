#ifndef _INDEX_WRITER_H_
#define _INDEX_WRITER_H_

#include <Document.h>
#include <Dictionary.h>
#include <string>

using namespace std;

class IndexWriter {
private:
	const string &dirPath;
public:
	IndexWriter(const string &dirPath);
	virtual void write(Document &doc);
	virtual void close();
	virtual void merge();
	virtual ~IndexWriter() {}
};

#endif
