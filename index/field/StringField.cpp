#include <StringField.h>

void StringField::writeTo(MMIndex &mmIndex) const {
}

string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	res += str;
	res += ">";
	return res; 
}


