#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
using namespace std;

class Token {
public:
	string value;
	size_t begin;
	size_t end;
public:
	Token() {}
	Token(const string &value, size_t begin, size_t end) :
		value(value), begin(begin), end(end) {}
	string toString() const;
};

#endif
