#ifndef _DICT_H_
#define _DICT_H_

#include <unordered_map>
#include <string>

using namespace std;

class AbstractDict {
public:
	virtual void add(const string &token) = 0;
	virtual size_t getTokenID(const string &token) const = 0;
	virtual ~AbstractDict() {}
};

class NormalDict : public AbstractDict {
private:
	unordered_map<string, int> dict;
public:
	void add(const string &token);
	size_t getTokenID(const string &token) const;
};

class HugeDict : public AbstractDict {
private:
	string filePath;
public:
	HugeDict(const string &filePath);
	void add(const string &token);
	size_t getTokenID(const string &token) const;
};

#endif
