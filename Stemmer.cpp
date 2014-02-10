#include "Stemmer.h"
#include <vector>
#include <string>
#include <ctype.h>
#include <string.h>

using namespace std;

inline bool Stemmer::isAccept(char c, const char *accept) const {
	size_t len = strlen(accept);
	for (size_t i = 0; i < len; i ++)
		if ( accept[i] == c ) return true;
	return false;
}

inline bool Stemmer::isTokenChar(char c) const {
	return isalnum(c) || isAccept(c, "&");
}

vector<string> Stemmer::tokenize(const string &text) const {
	size_t begin = 0;
	while ( begin < text.length() && !isTokenChar(text[begin]) ) begin ++;
	vector<string> res;
	while ( begin < text.length() ) {
		size_t end = begin + 1;
		while ( end < text.length() && isTokenChar(text[end]) ) end ++;
		string token = text.substr(begin, end - begin);
		res.push_back(token);
		begin = end;
		while ( begin < text.length() && !isTokenChar(text[begin]) ) begin ++;
	}
	return res;
}


