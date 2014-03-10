#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
using namespace std;

class Token {
public:
	string value;
	size_t begin;
	size_t end;
	size_t pos;
public:
	Token() {}
	Token(const string &value, size_t begin, size_t end, size_t pos=0) :
		value(value), begin(begin), end(end), pos(pos) {}
	virtual string toString() const;
	virtual ~Token() {}
};

#endif
