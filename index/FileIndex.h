#ifndef _FILE_INDEX_H_
#define _FILE_INDEX_H_

#include <fstream>
#include <string>

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
	virtual inline size_t getTermNum() const { return TERM_NUM; }
	virtual string fetchTerm(size_t termID);
	virtual ~FileIndex();
};


#endif
