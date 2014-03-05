#include <TokenStream.h>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

bool TokenStream::isSpecialAccept(char c, const char *accept) const {
	if ( accept == NULL ) return false;
	size_t i = 0;
	while ( accept[i] ) {
		if ( accept[i] == c ) return true;
		i ++;
	}
	return false;
}

bool TokenStream::isTokenChar(char c) const {
	return isalnum(c) || isSpecialAccept(c, "&");
}

TokenStream::TokenStream(istream &in) : in(in) {
//	in.seekg(0);
	while ( !in.eof() && !isTokenChar(in.peek()) ) in.get();
}

bool TokenStream::hasNext() const {
	return in;
}

Token TokenStream::next() {
	string str;
	size_t begin, end;
	if ( !in.eof() ) {
		begin = (size_t) in.tellg();
		str.push_back(in.get());
		while ( !in.eof() && isTokenChar(in.peek()) )
			str.push_back(in.get());
		end = in.tellg();

		/* To Lower Case */
		transform(str.begin(), str.end(), 
				str.begin(), ptr_fun<int, int>(tolower));

		while ( !in.eof() && !isTokenChar(in.peek()) ) in.get();
	}
	return Token(str, begin, end);
}

