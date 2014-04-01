#ifndef _FIELD_H_
#define _FIELD_H_

#include <map>
#include <string>
#include <util.h>

using namespace std;

class MMIndex;
class FieldNameMap;

class Field {
protected:
	string fieldName;
	Field(const string &fieldName) : fieldName(fieldName) {}
public:
	virtual void writeTo(MMIndex &mmIndex, 
			const FieldNameMap &fieldNameMap, size_t docID) = 0;
	virtual inline void save(ostream &cntOut, size_t fieldID) const {
		util::codec.encode(cntOut, fieldID);
		util::codec.encode(cntOut, getDL());
		util::codec.encode(cntOut, length());
	}
	virtual inline size_t getDL() const { return 1; }
	virtual inline size_t length() const { return 0; }
	virtual inline string get() const { return ""; }
	virtual string toString() const = 0;
	virtual const string &getFieldName() const { return fieldName; }
	virtual ~Field() {};
};

#endif
