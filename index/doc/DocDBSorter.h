#ifndef _DOC_DB_SORTER_H_
#define _DOC_DB_SORTER_H_


#include <DocDB.h>


class DocDBSorter {
private:
	DocDB *docDB;
	ofstream docOut;
	FieldNameMap &fieldNameMap;

public:
	DocDBSorter(const string &prefix, FieldNameMap &fieldNameMap);
	virtual void sort();
	virtual void close();
	virtual ~DocDBSorter() {}
};

#endif
