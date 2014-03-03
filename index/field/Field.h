#ifndef _FIELD_H_
#define _FIELD_H_

#include <map>
#include <string>

using namespace std;

class MMIndex;

class Field {
protected:
	string fieldName;
	Field(const string &fieldName) : fieldName(fieldName) {}
public:
	virtual void writeTo(MMIndex *mmIndex, 
			const map<string, size_t> &fieldIDMap, size_t docID) const = 0;
	virtual string toString() const = 0;
	virtual const string &getFieldName() const { return fieldName; }
	virtual ~Field() {};
};

#endif
