#ifndef _TOKEN_STREAM_H_
#define _TOKEN_STREAM_H_

#include <istream>
#include <Token.h>
#include <string>
using namespace std;

class TokenStream {
private:
	istream &in;

	bool isSpecialAccept(char c, const char *accept) const;
	bool isTokenChar(char c) const;
public:
	TokenStream(istream& in);
	virtual bool hasNext() const;
	virtual Token next();
	virtual ~TokenStream() {}
};


#endif
