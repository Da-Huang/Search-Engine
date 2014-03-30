#ifndef _FILE_INDEX_H_
#define _FILE_INDEX_H_

#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <ScoreDoc.h>
#include <PostingStream.h>

using namespace std;


class FileIndex {
private:
	ifstream idxIn;
	ifstream trmIn;
	ifstream pstIn;
	const size_t FIELD_NUM;
	const size_t RECORD_SIZE;
	size_t TERM_NUM;

	static const size_t FIELD_DATA_SIZE = 3 * sizeof(size_t);
	static const size_t TERM_DATA_SIZE = 1 * sizeof(size_t);

public:
	FileIndex(const string &prefix, size_t fieldNum);
	virtual size_t findTermID(const string &term);
	virtual size_t findGETermID(const string &term);
	virtual size_t findLTTermID(const string &term);
	virtual inline size_t getTermNum() const { return TERM_NUM; }
	virtual inline size_t getFieldNum() const { return FIELD_NUM; }
	tuple<size_t, size_t, size_t> getPostingListInfo(
			size_t termID, size_t fieldID);
	virtual vector<ScoreDoc> search(size_t fieldID, const string &term);

	virtual PostingStream* fetchPostingStream(
			size_t fieldID, const string &term);
	virtual PostingStream* fetchPostingStream(
			size_t fieldID, size_t termID);

	virtual string fetchTerm(size_t termID);
	virtual string toString();
	virtual ~FileIndex();

	friend class IndexMerger;
};

#endif
