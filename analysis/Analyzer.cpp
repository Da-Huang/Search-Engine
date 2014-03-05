#include <Analyzer.h>


TokenStream& Analyzer::tokenStream(istream &in) const {
	return *new TokenStream(in);
}
