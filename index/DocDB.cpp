#include <DocDB.h>
#include <FieldNameMap.h>
#include <StringField.h>


DocDB::DocDB(const string &prefix, const FieldNameMap &fieldNameMap) 
	: RECORD_SIZE(sizeof(size_t) * 2), fieldNameMap(fieldNameMap) {
	string docPath = prefix;
	docPath += ".doc";
	string cntPath = prefix;
	cntPath += ".cnt";

	docIn.open(docPath);
	cntIn.open(cntPath);

	docIn.seekg(0, ios::end);
	DOC_NUM = docIn.tellg() / RECORD_SIZE;
}

Document DocDB::fetchDocument(size_t docID) {
	Document res;
	if ( docID == 0 || docID > DOC_NUM ) return res;
	size_t cntBegin;
	size_t cntSize;
	docIn.seekg((docID - 1) * RECORD_SIZE);
	docIn.read((char*)&cntBegin, sizeof(cntBegin));
	docIn.read((char*)&cntSize, sizeof(cntSize));

	cntIn.seekg(cntBegin);
	for (size_t i = 0; i < cntSize; i ++) {
		size_t fieldID;
		cntIn.read((char*)&fieldID, sizeof(fieldID));
		string fieldName = fieldNameMap.getFieldName(fieldID);
		string str;
		getline(cntIn, str, '\0');
		res.addField(*new StringField(fieldName, str));
	}

	return res;
}

string DocDB::toString() {
	string res = "fieldNameMap:";
	res += fieldNameMap.toString();
	res += "\n";
	res += "doc:\n";
	for (size_t i = 1; i <= DOC_NUM; i ++) {
		res += to_string(i);
		res += ".";
		res += fetchDocument(i).toString();
		res += "\n";
	}
	return res;
}

DocDB::~DocDB() {
	docIn.close();
	cntIn.close();
}


