#ifndef _STEMMER_H_
#define _STEMMER_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stemmer {
public:
	Stemmer() {}
	vector<string> tokenize(const string &text) const;
};

#endif

