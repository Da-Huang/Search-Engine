#include <WSTokenStream.h>
#include <iostream>

using namespace std;


WSTokenStream::WSTokenStream(istream &in) : TokenStream(in, NULL) {
	while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
}

bool WSTokenStream::isTokenChar(char c) const {
	return isalnum(c) || isSpecialAccept(c, "&|!()");
}

Token WSTokenStream::next() {
	string str;
	size_t begin = in.tellg(), end = in.tellg();
	if ( hasNext() ) {
		str.push_back(in.get());
		while ( hasNext() && isTokenChar(in.peek()) )
			str.push_back(in.get());
		end = in.tellg();

		while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
	}
	return Token(str, begin, end);
}


