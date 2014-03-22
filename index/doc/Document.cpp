#include <IndexWriter.h>
#include <Document.h>


string Document::get(const string &fieldName) const {
	auto it = fields.find(fieldName);
	if ( it == fields.end() ) return "";
	return it->second.get();
}

void Document::addField(Field &field) {
	fields.insert(pair<string, Field&>(field.getFieldName(), field));
}

string Document::toString() const {
	string res = "[";
	for (auto it = fields.begin(); it != fields.end(); it ++) {
		res += it->second.toString();
		res += ",";
	}
	if ( res.back() == ',' ) res.erase(res.length() - 1);
	res.push_back(']');
	return res;
}

Document::~Document() {
	for (auto it = fields.begin(); it != fields.end(); it ++)
		if ( size_t(&it) > size_t(&(it->second)) ) delete &(it->second);
}


