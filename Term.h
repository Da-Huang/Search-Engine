#ifndef _TERM_H_
#define _TERM_H_

#include <string>

using namespace std;

class Term {
protect:
	string term;
	ifstream postingList;
	size_t begin;
	size_t end;
public:
	Term(const string &term) : term(term) {}
};

#endif
