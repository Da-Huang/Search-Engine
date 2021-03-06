#ifndef _FIELD_NAME_MAP_H_
#define _FIELD_NAME_MAP_H_


#include <iostream>
#include <vector>
#include <Field.h>

using namespace std;

class FieldNameMap {
private:
	vector<string> fieldNames;
	map<string, size_t> fieldIDMap;
	vector<size_t> sumdls;
	vector<double> avgdls;

public:
	const string &getFieldName(size_t fieldID) const;
	virtual size_t getFieldID(const string &fieldName) const;
	virtual void addFieldName(const string &fieldName);

	virtual void initSumdls();
	virtual void addToSumdl(size_t fieldID, size_t dl);
	virtual void genAvgdls(size_t DOC_NUM);
	virtual double getAvgdl(size_t fieldID) const;

	virtual string toString() const;
	virtual void load(istream &in);
	virtual void save(ostream &out);
	virtual inline size_t size() const { return fieldNames.size(); }
	virtual ~FieldNameMap() {}
};


#endif
