#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include "TokenStream.h"

class Analyzer {
public:
	virtual TokenStream tokenStream() = 0;
};

#endif
