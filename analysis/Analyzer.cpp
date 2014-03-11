#include <cstring>
#include <algorithm>
#include <Analyzer.h>
#include <util.h>


void Analyzer::refine(string &str) const {
	transform(str.begin(), str.end(), 
			str.begin(), ptr_fun<int, int>(tolower));
	str = util::stem(str);
}

/** should be deleted after called */
TokenStream& Analyzer::tokenStream(istream &in) const {
	return *new TokenStream(in, *this);
}
