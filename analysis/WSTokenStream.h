#ifndef _WS_TOKEN_STREAM_H_
#define _WS_TOKEN_STREAM_H_

#include <TokenStream.h>


class WSTokenStream : public TokenStream {
protected:
	inline bool isTokenChar(char c) const { return c != ' '; }
	WSTokenStream(istream& in, const Analyzer &analyzer, void *null)
		: TokenStream(in, analyzer, null) {}
public:
	WSTokenStream(istream& in, const Analyzer &analyzer);
	virtual Token next();
	virtual ~WSTokenStream() {}
};

#endif
