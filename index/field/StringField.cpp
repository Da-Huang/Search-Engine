#include <StringField.h>


string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	res += str;
	res += ">";
	return res; 
}


