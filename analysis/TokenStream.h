#ifndef _TOKEN_STREAM_H_
#define _TOKEN_STREAM_H_

#include <istream>
#include <Token.h>
#include <string>
using namespace std;

class TokenStream {
private:
	istream &in;
	size_t size;
public:
	TokenStream(istream& in);
	bool hasNext() const;
	Token next();
	bool isSpecialAccept(char c, const char *accept) const;
	bool isTokenChar(char c) const;
};


#endif
