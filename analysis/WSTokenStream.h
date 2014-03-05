#ifndef _WS_TOKEN_STREAM_H_
#define _WS_TOKEN_STREAM_H_

#include <TokenStream.h>

class WSTokenStream : public TokenStream {
public:
	WSTokenStream(istream& in);
	virtual bool hasNext() const;
	virtual Token next();
	virtual ~WSTokenStream() {}
};

#endif
