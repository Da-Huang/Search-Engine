#include <IndexWriter.h>
#include <Document.h>

/*
StringField Document::getStringField(const string &fieldName) {
	auto it = fields.getFieldName();
	if ( it == fields.end() ) return new StringField();
}
*/

void Document::addField(Field &field) {
	fields.insert(pair<string, Field&>(field.getFieldName(), field));
}

string Document::toString() const {
	string res = "[";
	for (auto it = fields.begin(); it != fields.end(); it ++) {
		res += it->second.toString();
		res += ",";
	}
	if ( res.length() > 1 ) res.erase(res.length() - 1);
	res.push_back(']');
	return res;
}

Document::~Document() {
	for (auto it = fields.begin(); it != fields.end(); it ++)
		if ( (size_t)&it > (size_t)&(it->second) ) delete &(it->second);
}


