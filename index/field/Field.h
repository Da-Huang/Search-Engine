#ifndef _FIELD_H_
#define _FIELD_H_

#include <string>

using namespace std;

class Field {
protected:
	string fieldName;
	Field(const string &fieldName) : fieldName(fieldName) {}
public:
	virtual string toString() const = 0;
	virtual const string &getFieldName() const { return fieldName; }
};

#endif
