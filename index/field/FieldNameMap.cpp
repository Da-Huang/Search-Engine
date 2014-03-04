#include <FieldNameMap.h>


const string& FieldNameMap::getFieldName(size_t fieldID) const {
	return fieldNames[fieldID - 1];
}


size_t FieldNameMap::getFieldID(const string &fieldName) const {
	auto it = fieldIDMap.find(fieldName);
	if ( it == fieldIDMap.end() ) return 0;
	return it->second;
}


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
	if ( res[res.length() - 1] == ',' ) res.erase(res.length() - 1);
	res += "}";
	return res;
}

void FieldNameMap::load(istream &in) {
	in.seekg(0);
	size_t N;
	in.read((char*)&N, sizeof(N));
	size_t i = 0;
	string line;
	while ( i ++ < N && getline(in, line, '\0') ) {
		addFieldName(line);
	}
}

void FieldNameMap::save(ostream &out) {
	for (auto it = fieldNames.begin(); it != fieldNames.end(); it ++)
		out.write(it->c_str(), it->length() + 1);
}


