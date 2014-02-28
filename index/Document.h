#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "field/Field.h"
#include <string>
#include <map>

using namespace std;

class Document {
private:
	map<string, Field&> fields;
public:
	void addField(Field &field);
	string toString() const;
};

void Document::addField(Field &field) {
	fields.insert(pair<string, Field&>(field.getFieldName(), field));
}

string Document::toString() const {
	string res = "[";
	for (auto it = fields.begin(); it != fields.end(); it ++) {
		res += it->second.toString();
		res += ", ";
	}
	if ( res.length() > 1 ) res.erase(res.length() - 1);
	res.push_back(']');
	return res;
}


#endif
