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
	N = idxIn.tellg() / RECORD_SIZE;
}


string FileIndex::fetchTerm(size_t termID) {
	return "";
}
