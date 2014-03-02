#include <IndexWriter.h>
#include <Document.h>

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


