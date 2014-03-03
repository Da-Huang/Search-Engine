#include <StringField.h>

void StringField::writeTo(MMIndex &mmIndex, size_t docID) const {
	mmIndex.add(str, fieldName, Posting(docID));
}

string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	res += str;
	res += ">";
	return res; 
}


