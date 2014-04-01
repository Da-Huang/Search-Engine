#include <DocDB.h>
#include <util.h>
#include <FieldNameMap.h>
#include <StringField.h>


DocDB::DocDB(const string &prefix, const FieldNameMap &fieldNameMap, 
		size_t FIELD_NUM) 
	: fieldNameMap(fieldNameMap), FIELD_NUM(FIELD_NUM),
		RECORD_SIZE(FIELD_DATA_SIZE * FIELD_NUM + DOC_DATA_SIZE) {

	docIn.open(util::join("", {prefix, ".doc"}));
	cntIn.open(util::join("", {prefix, ".cnt"}));

	docIn.seekg(0, ios::end);
	DOC_NUM = docIn.tellg() / RECORD_SIZE;
}

size_t DocDB::getDocFieldDL(size_t docID, size_t fieldID) {
	const size_t BASE = (docID - 1) * RECORD_SIZE + DOC_DATA_SIZE;
	docIn.seekg(BASE + (fieldID - 1) * FIELD_DATA_SIZE);
	size_t dl;
	docIn.read((char*)&dl, sizeof(dl));
	return dl;
}

tuple<size_t, size_t> DocDB::getDocCntInfo(size_t docID) {
	const size_t BASE = (docID - 1) * RECORD_SIZE;
	docIn.seekg(BASE);
	size_t cntBegin, cntSize;
	docIn.read((char*)&cntBegin, sizeof(cntBegin));
	docIn.read((char*)&cntSize, sizeof(cntSize));
	return make_tuple(cntBegin, cntSize);
}

Document DocDB::fetchDocument(size_t docID) {
	Document res;
	if ( docID == 0 || docID > DOC_NUM ) return res;

	size_t cntBegin, cntSize;
	tie(cntBegin, cntSize) = getDocCntInfo(docID);
	cntIn.seekg(cntBegin);
	for (size_t i = 0; i < cntSize; i ++) {
		size_t fieldID = util::codec.decode(cntIn);
		/*size_t dl =*/ util::codec.decode(cntIn);
		size_t length = util::codec.decode(cntIn);

		if ( length ) {
			string str;
			getline(cntIn, str, '\0');
			string fieldName = fieldNameMap.getFieldName(fieldID);
			res.addField(*new StringField(fieldName, str));
		}
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


