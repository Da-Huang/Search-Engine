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

size_t FileIndex::findTermID(const string &term) {
	size_t first = 1, last = TERM_NUM;
	while ( first <= last ) {
		size_t mid = (first + last) / 2;
		string midStr = fetchTerm(mid);
		if ( midStr < term ) first = mid + 1;
		else if ( midStr > term ) last = mid - 1; 
		else return mid;
	}
	return 0;
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

size_t FileIndex::getFieldNum() const {
	return (RECORD_SIZE / sizeof(size_t) - 1) / 2;
}

pair<size_t, size_t> FileIndex::getPostingListInfo(
		size_t termID, size_t fieldID) {
	size_t BASE = (termID - 1) * RECORD_SIZE + 
					RECORD_SIZE - getFieldNum() * 2 * sizeof(size_t);
	idxIn.seekg(BASE + (fieldID - 1) * 2 * sizeof(size_t));
	size_t pstListBegin, pstListSize;
	idxIn.read((char*)&pstListBegin, sizeof(pstListBegin));
	idxIn.read((char*)&pstListSize, sizeof(pstListSize));
	return make_pair(pstListBegin, pstListSize);
}

string FileIndex::toString() {
	string res = "index:\n";
	for (size_t i = 1; i <= TERM_NUM; i ++) {
		res += to_string(i);
		res += ".";
		res += fetchTerm(i);
		res += ":";
		for (size_t j = 1; j <= getFieldNum(); j ++) {
			pair<size_t, size_t> pstListInfo = getPostingListInfo(i, j);
			size_t pstListBegin = pstListInfo.first;
			size_t pstListSize = pstListInfo.second;
		}
		res += "[";
		res += "]";
		res += "\n";
	}
	return res;
}

FileIndex::~FileIndex() {
	idxIn.close();
	trmIn.close();
	pstIn.close();
}


