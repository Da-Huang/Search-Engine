#include <BoolAnalyzer.h>
#include <WSTokenStream.h>


TokenStream& BoolAnalyzer::tokenStream(istream &in) const {
	return *new WSTokenStream(in, *this);
}
