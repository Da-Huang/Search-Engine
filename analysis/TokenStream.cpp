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
	in.seekg(0);
	while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
}

bool TokenStream::hasNext() const {
	return !in.eof() && in.peek();
}

Token TokenStream::next() {
//	while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
	string str;
	size_t begin = in.tellg(), end = in.tellg();
	if ( hasNext() ) {
		str.push_back(in.get());
		while ( hasNext() && isTokenChar(in.peek()) )
			str.push_back(in.get());
		end = in.tellg();

		/* To Lower Case */
		transform(str.begin(), str.end(), 
				str.begin(), ptr_fun<int, int>(tolower));

		while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
	}
	return Token(str, begin, end);
}

