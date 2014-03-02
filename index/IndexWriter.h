#ifndef _INDEX_WRITER_H_
#define _INDEX_WRITER_H_

#include <Document.h>
#include <Dictionary.h>

class IndexWriter {
private:
//	string DIR
	Dictionary dict;
public:
	void write(Document &doc);
	void close();
};

#endif
