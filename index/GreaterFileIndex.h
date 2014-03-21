#ifndef _GREATER_FILE_INDEX_H_
#define _GREATER_FILE_INDEX_H_

#include <FileIndex.h>
#include <vector>

using namespace std;


class GreaterFileIndex {
private:
	const vector<FileIndex*> &fileIndexes;
	const vector<size_t> &termIndex;
public:
	GreaterFileIndex(const vector<FileIndex*> &fileIndexes, 
			const vector<size_t> &termIndex) 
		: fileIndexes(fileIndexes), termIndex(termIndex) {}
	bool operator () (size_t i, size_t j) const {
		return fileIndexes[i]->fetchTerm(termIndex[i]) > 
			fileIndexes[j]->fetchTerm(termIndex[j]);
	}
};


#endif
