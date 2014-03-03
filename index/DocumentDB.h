#ifndef _DOCUMENT_DB_H_
#define _DOCUMENT_DB_H_

#include <fstream>
#include <Document.h>

using namespace std;


class DocumentDB {
private:
	ifstream docIn;
	ifstream cntIn;
	const size_t RECORD_SIZE;
	size_t N;
public:
	DocumentDB(const string &prefix);
	virtual Document fetchDocument(size_t docID) { return Document(); }
};

#endif
