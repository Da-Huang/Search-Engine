#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <unordered_map>
#include <string>

using namespace std;

class Dictionary {
protected:
	string filePath;
public:
	Dictionary(const string &filePath) : filePath(filePath) {}
	void add(const string &term);
	size_t getTermID(const string &term);
	virtual ~Dictionary();
};

#endif
