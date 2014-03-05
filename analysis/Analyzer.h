#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include <TokenStream.h>

class Analyzer {
public:
	/* The Return Value need to be deleted */
	virtual TokenStream& tokenStream(istream &in) const;
	virtual ~Analyzer() {}
};

#endif
