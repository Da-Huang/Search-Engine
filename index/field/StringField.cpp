#include <iostream>
#include <StringField.h>
#include <Posting.h>
#include <MMIndex.h>

void StringField::writeTo(MMIndex &mmIndex, 
		const map<string, size_t> &fieldIDMap, size_t docID) const {
	auto it = fieldIDMap.find(fieldName);
	if ( it == fieldIDMap.end() ) return;
	mmIndex.add(str, it->second, Posting(docID));
}

string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	res += str;
	res += ">";
	return res; 
}


