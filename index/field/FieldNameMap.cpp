#include <FieldNameMap.h>


const string& FieldNameMap::getFieldName(size_t fieldID) const {
	return fieldNames[fieldID - 1];
}


size_t FieldNameMap::getFieldID(const string &fieldName) const {
	auto it = fieldIDMap.find(fieldName);
	if ( it == fieldIDMap.end() ) return 0;
	return it->second;
}

/** Add Field Name if it does not exist. **/
void FieldNameMap::addFieldName(const string &fieldName) {
	if ( getFieldID(fieldName) > 0 ) return;
	fieldNames.push_back(fieldName);
	fieldIDMap[fieldName] = fieldNames.size();
}

string FieldNameMap::toString() const {
	string res = "{";
	for (auto it = fieldIDMap.begin(); it != fieldIDMap.end(); it ++) {
		res += it->first;
		res += "=";
		res += to_string(it->second);
		res += ",";
	}
	if ( res.back() == ',' ) res.erase(res.length() - 1);
	res += "}";
	return res;
}

void FieldNameMap::load(istream &in) {
	in.seekg(sizeof(size_t));
	string line;
	while ( getline(in, line, '\0') ) addFieldName(line);
}

void FieldNameMap::save(ostream &out) {
	for (auto it = fieldNames.begin(); it != fieldNames.end(); it ++)
		out.write(it->c_str(), it->length() + 1);
}


