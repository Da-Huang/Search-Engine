#include <DocumentDB.h>


DocumentDB::DocumentDB(const string &prefix) 
	: RECORD_SIZE(sizeof(size_t) * 2) {
	string docPath = prefix;
	docPath += ".doc";
	string cntPath = prefix;
	cntPath += ".cnt";

	docIn.open(docPath);
	cntIn.open(cntPath);

	docIn.seekg(0, ios::end);
	N = docIn.tellg() / RECORD_SIZE;
}
