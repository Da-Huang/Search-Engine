#ifndef _WS_TOKEN_STREAM_H_
#define _WS_TOKEN_STREAM_H_

#include <TokenStream.h>

class WSTokenStream : public TokenStream {
protected:
	bool isTokenChar(char c) const;
	WSTokenStream(istream& in, void *null) : TokenStream(in, null) {}
public:
	WSTokenStream(istream& in);
	virtual Token next();
	virtual ~WSTokenStream() {}
};

#endif
