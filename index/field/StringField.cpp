#include <iostream>
#include <Posting.h>
#include <MMIndex.h>
#include <StringField.h>
#include <FieldNameMap.h>
#include <Field.h>


void StringField::writeTo(MMIndex &mmIndex, 
		const FieldNameMap &fieldNameMap, size_t docID) {
	size_t fieldID = fieldNameMap.getFieldID(fieldName);
	if ( fieldID == 0 ) return;
	mmIndex.add(str, fieldID, Posting(docID));
}

void StringField::save(ostream &cntOut, size_t fieldID) const {
	Field::save(cntOut, fieldID);
	cntOut.write(str.c_str(), str.length() + 1);
}

string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ":";
	res += str;
	res += ">";
	return res; 
}


