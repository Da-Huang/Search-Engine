#ifndef _DICT_H_
#define _DICT_H_

#include "Dict.h"
#include <unordered_map>
#include <string>

using namespace std;

class AbstractDict {
protected:
	string filePath;
public:
	AbstractDict(const string &filePath) : filePath(filePath) {}
	virtual void add(const string &term) = 0;
	virtual size_t getTermID(const string &term) const = 0;
	virtual ~AbstractDict() {}
};

class NormalDict : public AbstractDict {
private:
	unordered_map<string, int> dict;
public:
	NormalDict(const string &filePath, bool isNew=false);
	void add(const string &term);
	size_t getTermID(const string &term) const;
	~NormalDict();
	friend ostream &operator << (ostream &out, const NormalDict &dict);
	friend istream &operator >> (istream &in, NormalDict &dict);
};

class HugeDict : public AbstractDict {
public:
	void add(const string &term);
	size_t gettermID(const string &term) const;
};

#endif
