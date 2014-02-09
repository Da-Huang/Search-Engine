#include "stemmer.h"
#include <vector>
#include <string>
#include <ctype.h>

using namespace std;

vector<string> Stemmer::tokenize(const string &text) const {
	size_t begin = 0;
	while ( begin < text.length() && isspace(text[begin]) ) begin ++;
	vector<string> res;
	while ( begin < text.length() ) {
		size_t end = begin + 1;
		while ( end < text.length() && !isspace(text[end]) ) end ++;
		string token = text.substr(begin, end - begin);
		res.push_back(token);
		begin = end;
		while ( begin < text.length() && isspace(text[begin]) ) begin ++;
	}
	return res;
}


