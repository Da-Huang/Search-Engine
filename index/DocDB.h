#ifndef _DOC_DB_H_
#define _DOC_DB_H_

#include <fstream>
#include <Document.h>

using namespace std;

class FieldNameMap;

class DocDB {
private:
	ifstream docIn;
	ifstream cntIn;
	const size_t RECORD_SIZE;
	size_t DOC_NUM;
	const FieldNameMap &fieldNameMap;
public:
	DocDB(const string &prefix, const FieldNameMap& fieldNameMap);
	virtual Document fetchDocument(size_t docID);
	virtual inline size_t getDocNum() const { return DOC_NUM; }
	virtual ~DocDB();
};

#endif
