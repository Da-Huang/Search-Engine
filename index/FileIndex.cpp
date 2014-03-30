#include <iostream>
#include <util.h>
#include <FileIndex.h>
#include <PostingStream.h>


FileIndex::FileIndex(const string &prefix, size_t fieldNum)
	: FIELD_NUM(fieldNum), 
		RECORD_SIZE(FIELD_NUM * FIELD_DATA_SIZE + TERM_DATA_SIZE) {

	idxIn.open(util::join("", {prefix, ".idx"}));
	trmIn.open(util::join("", {prefix, ".trm"}));
	pstIn.open(util::join("", {prefix, ".pst"}));

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

pair<size_t, size_t> FileIndex::getPostingListInfo(
		size_t termID, size_t fieldID) {
	const size_t BASE = (termID - 1) * RECORD_SIZE + TERM_DATA_SIZE;
	idxIn.seekg(BASE + (fieldID - 1) * FIELD_DATA_SIZE);
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
		for (size_t j = 1; j <= FIELD_NUM; j ++) {
			res += to_string(j);
			res += "'[";

			PostingStream* ps = fetchPostingStream(j, i);
			if ( ps ) {
				while ( ps->hasNext() ) {
					Posting posting = ps->next();
					res += posting.toString();
					res += ",";
				}
				delete ps;
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


