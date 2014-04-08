#ifndef _DOC_DB_H_
#define _DOC_DB_H_

#include <tuple>
#include <fstream>
#include <Document.h>

using namespace std;


class FieldNameMap;

class DocDB {
private:
	ifstream docIn;
	ifstream cntIn;
	const FieldNameMap &fieldNameMap;

	size_t DOC_NUM;
	const size_t FIELD_NUM;
	const size_t RECORD_SIZE;

	static const size_t DOC_DATA_SIZE = 
					sizeof(double) + 2 * sizeof(size_t);
	static const size_t FIELD_DATA_SIZE = 1 * sizeof(size_t);

public:
	DocDB(const string &prefix, const FieldNameMap &fieldNameMap, 
			size_t FIELD_NUM=0);
	virtual size_t getDocFieldDL(size_t docID, size_t fieldID);
	virtual double getDocStaticScore(size_t docID);
	virtual tuple<size_t, size_t> getDocCntInfo(size_t docID);
	virtual Document fetchDocument(size_t docID);
	virtual inline size_t getDocNum() const { return DOC_NUM; }
	virtual string toString();
	virtual ~DocDB();

	friend class DocDBSorter;
};

#endif
