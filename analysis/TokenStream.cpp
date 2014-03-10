#include <TokenStream.h>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;


size_t TokenStream::getLength() const {
	size_t origin = in.tellg();
	in.seekg(0, ios::end);
	size_t res = in.tellg();
	in.seekg(origin);
	return res;
}

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

TokenStream::TokenStream(istream &in) : in(in), LEN(getLength()), pos(0) {
	in.seekg(0);
	while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
}

TokenStream::TokenCharType TokenStream::getTokenCharType(char c) const {
	if ( isdigit(c) ) return NUMBER;
	else if ( isalpha(c) ) return ALPHA;
	else if ( isTokenChar(c) ) return SPECIAL;
	else return ILLEGAL;
}

bool TokenStream::hasNext() const {
	return !in.eof() && (size_t) in.tellg() != LEN;
}

Token TokenStream::next() {
	string str;
	size_t begin = in.tellg(), end = in.tellg();
	if ( hasNext() ) {
		str.push_back(in.get());
		while ( hasNext() && isTokenChar(in.peek()) &&
			getTokenCharType(in.peek()) == getTokenCharType(str.back()) )
			str.push_back(in.get());
		end = in.tellg();

		/* To Lower Case */
		transform(str.begin(), str.end(), 
				str.begin(), ptr_fun<int, int>(tolower));

		while ( hasNext() && !isTokenChar(in.peek()) ) in.get();
	}
	return Token(str, begin, end, ++ pos);
}

