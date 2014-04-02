#include <cassert>
#include <FieldNameMap.h>


const string& FieldNameMap::getFieldName(size_t fieldID) const {
	return fieldNames[fieldID - 1];
}

void FieldNameMap::initSumdls() {
	sumdls.clear();
	sumdls.insert(sumdls.end(), size(), 0);
}

void FieldNameMap::addToSumdl(size_t fieldID, size_t dl) {
	sumdls[fieldID - 1] += dl;
}

void FieldNameMap::genAvgdls(size_t DOC_NUM) {
	avgdls.clear();
	for (size_t i = 0; i < size(); i ++)
		avgdls.push_back(double(sumdls[i]) / DOC_NUM);
}

double FieldNameMap::getAvgdl(size_t fieldID) const {
	return avgdls[fieldID - 1];
}

size_t FieldNameMap::getFieldID(const string &fieldName) const {
	auto it = fieldIDMap.find(fieldName);
	if ( it == fieldIDMap.end() ) return 0;
	return it->second;
}

/** Add Field Name if it does not exist. **/
void FieldNameMap::addFieldName(const string &fieldName) {
	if ( getFieldID(fieldName) ) return;
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
	while ( getline(in, line, '\0') ) {
		addFieldName(line);
		double avgdl;
		in.read((char*)&avgdl, sizeof(avgdl));
		avgdls.push_back(avgdl);
	}
}

void FieldNameMap::save(ostream &out) {
	assert (size() == avgdls.size());
	for (size_t i = 0; i < size(); i ++) {
		out.write(fieldNames[i].c_str(), fieldNames[i].length() + 1);
		out.write((char*)&avgdls[i], sizeof(avgdls[i]));
	}
}


