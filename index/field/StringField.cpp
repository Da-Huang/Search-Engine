#include <iostream>
#include <Posting.h>
#include <MMIndex.h>
#include <StringField.h>
#include <FieldNameMap.h>
#include <Field.h>


void StringField::writeTo(MMIndex &mmIndex, 
		const FieldNameMap &fieldNameMap, size_t docID) const {
	size_t fieldID = fieldNameMap.getFieldID(fieldName);
	if ( fieldID == 0 ) return;
	mmIndex.add(str, fieldID, Posting(docID));
}

string StringField::toString() const {
	string res = "<";
	res += fieldName;
	res += ":";
	res += str;
	res += ">";
	return res; 
}


