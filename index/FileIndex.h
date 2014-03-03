#ifndef _FILE_INDEX_H_
#define _FILE_INDEX_H_

#include <fstream>
#include <string>

using namespace std;


class FileIndex {
private:
	ifstream idxIn;
	ifstream trmIn;
	ifstream pstIn;
	const size_t RECORD_SIZE;
	size_t N;
public:
	FileIndex(const string &prefix, size_t recordSize);
	virtual string fetchTerm(size_t termID);
};


#endif
