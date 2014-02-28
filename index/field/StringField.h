#ifndef _STRING_FIELD_H_
#define _STRING_FIELD_H_

#include "Field.h"
#include <string>
using namespace std;

class StringField : public Field {
private:
	string str;
public:
	StringField(const string &fieldName, const string &str) :
		Field(fieldName), str(str) {}
	virtual string toString() const;
};


string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	res += str;
	res += ">";
	return res; 
}


#endif
