#include "StringField.h"

#include <string>

using namespace std;


string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	res += str;
	res += ">";
	return res; 
}


