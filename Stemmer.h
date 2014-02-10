#ifndef _STEMMER_H_
#define _STEMMER_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stemmer {
private:
	inline bool isAccept(char c, const char *accept) const;
 	inline bool isTokenChar(char c) const;
public:
	Stemmer() {}
	vector<string> tokenize(const string &text) const;
};

#endif

