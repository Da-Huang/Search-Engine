#include <iostream>
#include <FileIndex.h>
#include <PostingStream.h>


size_t FileIndex::recordSize() const {
	return (FIELD_NUM * 2 + 1) * sizeof(size_t);
}

FileIndex::FileIndex(const string &prefix, size_t fieldNum)
	: FIELD_NUM(fieldNum), RECORD_SIZE(recordSize()) {
//	cout << FIELD_NUM << " " << RECORD_SIZE << endl;
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

size_t FileIndex::findGETermID(const string &term) {
	size_t first = 1, last = TERM_NUM;
	while ( first < last ) {
		size_t mid = (first + last) / 2;
		string midStr = fetchTerm(mid);
		if ( midStr < term ) first = mid + 1;
		else if ( midStr > term ) last = mid - 1; 
		else return mid;
	}
	string firstStr = fetchTerm(first);
	return firstStr >= term ? first : first + 1;
}

size_t FileIndex::findLTTermID(const string &term) {
	size_t first = 1, last = TERM_NUM;
	while ( first < last ) {
		size_t mid = (first + last) / 2;
		string midStr = fetchTerm(mid);
		if ( midStr < term ) first = mid + 1;
		else if ( midStr > term ) last = mid - 1; 
		else return mid - 1;
	}
	string firstStr = fetchTerm(first);
	return firstStr < term ? first : first - 1;
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
	size_t pstListBegin, pstListEnd;
	idxIn.read((char*)&pstListBegin, sizeof(pstListBegin));
	idxIn.read((char*)&pstListEnd, sizeof(pstListEnd));
	return make_pair(pstListBegin, pstListEnd);
}

string FileIndex::toString() {
	string res = "index:\n";
	for (size_t i = 1; i <= TERM_NUM; i ++) {
		res += to_string(i);
		res += ".";
		res += fetchTerm(i);
		res += ": ";
		for (size_t j = 1; j <= getFieldNum(); j ++) {
			res += to_string(j);
			res += "'[";

			pair<size_t, size_t> pstListInfo = getPostingListInfo(i, j);
			size_t pstListBegin = pstListInfo.first;
			size_t pstListEnd = pstListInfo.second;
			PostingStream postingStream(pstIn, pstListBegin, pstListEnd);
			while ( postingStream.hasNext() ) {
				Posting posting = postingStream.next();
				res += posting.toString();
				res += ",";
			}
			if ( res.back() == ',' ) res.erase(res.length() - 1);
			res += "],";
		}
		if ( res.back() == ',' ) res.erase(res.length() - 1);
		res += "\n";
	}
	return res;
}

/** the result need to be deleted. **/
PostingStream* FileIndex::fetchPostingStream(
		size_t fieldID, size_t termID) {
	if ( termID == 0 || fieldID == 0 || termID > TERM_NUM ) return NULL;
	pair<size_t, size_t> pstListInfo = getPostingListInfo(termID, fieldID);
	size_t pstListBegin = pstListInfo.first;
	size_t pstListEnd = pstListInfo.second;
	if ( pstListBegin >= pstListEnd ) return NULL;
	return new PostingStream(pstIn, pstListBegin, pstListEnd);
}

/** the result need to be deleted. **/
PostingStream* FileIndex::fetchPostingStream(
		size_t fieldID, const string &term) {
	size_t termID = findTermID(term);
	return fetchPostingStream(fieldID, termID);
}

vector<ScoreDoc> FileIndex::search(size_t fieldID, const string &term) {
	vector<ScoreDoc> res;
	PostingStream* ps = fetchPostingStream(fieldID, term);
	if ( ps == NULL ) return res;

	while ( ps->hasNext() ) {
		res.push_back(ScoreDoc(ps->nextDocID()));
	}
	delete ps;

	return res;
}

FileIndex::~FileIndex() {
	idxIn.close();
	trmIn.close();
	pstIn.close();
}


