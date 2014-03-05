#include <WSTokenStream.h>
#include <iostream>

using namespace std;


WSTokenStream::WSTokenStream(istream &in) : TokenStream(in) {}

bool WSTokenStream::hasNext() const {
	return in;
}

bool WSTokenStream::isTokenChar(char c) const {
	return isalnum(c) || isSpecialAccept(c, "&|!()");
}

Token WSTokenStream::next() {
	while ( !in.eof() && !isTokenChar(in.peek()) ) in.get();

	string str;
	size_t begin = in.tellg(), end = in.tellg();
	if ( !in.eof() ) {
		str.push_back(in.get());
		while ( !in.eof() && isTokenChar(in.peek()) )
			str.push_back(in.get());
		end = in.tellg();

		while ( !in.eof() && !isTokenChar(in.peek()) ) in.get();
	}
	if ( in.eof() ) end = begin + str.length();
	return Token(str, begin, end);
}


