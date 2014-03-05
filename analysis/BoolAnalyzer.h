#ifndef _BOOL_ANALYZER_H_
#define _BOOL_ANALYZER_H_

#include <Analyzer.h>


class BoolAnalyzer : public Analyzer {
public:
	virtual TokenStream& tokenStream(istream &in) const;
	virtual ~BoolAnalyzer() {}
};

#endif
