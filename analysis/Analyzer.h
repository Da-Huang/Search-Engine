#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include <TokenStream.h>

class Analyzer {
public:
	virtual TokenStream tokenStream(istream &in);
	virtual ~Analyzer() {}
};

#endif
