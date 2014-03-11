#include <Analyzer.h>
#include <WSTokenStream.h>
#include <iostream>

using namespace std;


WSTokenStream::WSTokenStream(istream &in, const Analyzer &analyzer) 
	: TokenStream(in, analyzer, NULL) {
	while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
}

Token WSTokenStream::next() {
	string str;
	size_t begin = in.tellg(), end = in.tellg();
	if ( hasNext() ) {
		str.push_back(in.get());
		while ( hasNext() && isTokenChar(in.peek()) )
			str.push_back(in.get());
		end = in.tellg();

		analyzer.refine(str);

		while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
	}
	return Token(str, begin, end, ++ pos);
}


