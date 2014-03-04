#include <iostream>
#include <FileIndex.h>


FileIndex::FileIndex(const string &prefix, size_t recordSize)
	: RECORD_SIZE(recordSize) {
	string idxPath = prefix;
	idxPath += ".idx";
	string trmPath = prefix;
	trmPath += ".trm";
	string pstPath = prefix;
	pstPath += ".pst";

	idxIn.open(idxPath);
	trmIn.open(trmPath);
	pstIn.open(pstPath);

	idxIn.seekg(0, ios::end);
	TERM_NUM = idxIn.tellg() / RECORD_SIZE;
}


string FileIndex::fetchTerm(size_t termID) {
	if ( termID == 0 || termID > TERM_NUM ) return "";
	idxIn.seekg((termID - 1) * RECORD_SIZE);
	size_t trmBegin;
	idxIn.read((char*)&trmBegin, sizeof(trmBegin));
	trmIn.seekg(trmBegin);
	string res;
	getline(trmIn, res, '\0');
	return res;
}


FileIndex::~FileIndex() {
	idxIn.close();
	trmIn.close();
	pstIn.close();
}


