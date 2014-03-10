#ifndef _TOKEN_STREAM_H_
#define _TOKEN_STREAM_H_

#include <istream>
#include <Token.h>
#include <string>
using namespace std;

class TokenStream {
protected:
	istream &in;
	const size_t LEN;
	size_t pos;

	bool isSpecialAccept(char c, const char *accept) const;
	bool isTokenChar(char c) const;
	TokenStream(istream& in, void *null) 
		: in(in), LEN(getLength()), pos(0) {}

	enum TokenCharType {
		ILLEGAL, SPECIAL, NUMBER, ALPHA,
	};
	TokenCharType getTokenCharType(char c) const;
public:
	TokenStream(istream& in);
	virtual bool hasNext() const;
	virtual size_t getLength() const;
	virtual Token next();
	virtual ~TokenStream() {}
};


#endif
