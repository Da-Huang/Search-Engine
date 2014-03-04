#ifndef _FILE_INDEX_H_
#define _FILE_INDEX_H_

#include <fstream>
#include <string>
#include <utility>

using namespace std;


class FieldNameMap;

class FileIndex {
private:
	ifstream idxIn;
	ifstream trmIn;
	ifstream pstIn;
	const size_t RECORD_SIZE;
	size_t TERM_NUM;
public:
	FileIndex(const string &prefix, size_t recordSize);
	virtual size_t findTermID(const string &term);
	virtual inline size_t getTermNum() const { return TERM_NUM; }
	virtual pair<size_t, size_t> getPostingListInfo(
			size_t termID, size_t fieldID);
	virtual size_t getFieldNum() const;
	virtual string fetchTerm(size_t termID);
	virtual string toString();
	virtual ~FileIndex();
};


#endif
