#ifndef _TOKEN_STREAM_H_
#define _TOKEN_STREAM_H_

#include <istream>
#include <string>
#include <Token.h>

using namespace std;

class Analyzer;

class TokenStream {
protected:
	istream &in;
	const size_t LEN;
	size_t pos;
//	const Analyzer &analyzer;
	const Analyzer &analyzer;

	bool isSpecialAccept(char c, const char *accept) const;
	bool isTokenChar(char c) const;
	TokenStream(istream& in, const Analyzer &analyzer, void *null) 
		: in(in), LEN(getLength()), pos(0), analyzer(analyzer) {}

	enum TokenCharType {
		ILLEGAL, SPECIAL, NUMBER, ALPHA,
	};
	TokenCharType getTokenCharType(char c) const;
public:
	TokenStream(istream& in, const Analyzer &analyzer);
	virtual bool hasNext() const;
	virtual size_t getLength() const;
	virtual Token next();
	virtual ~TokenStream() {}
};


#endif
