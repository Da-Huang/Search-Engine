#ifndef _SNIPPET_H_
#define _SNIPPET_H_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <Analyzer.h>

using namespace std;


class Snippet {
private:
	const map<string, double> &terms;

	static string fetch(istream &in, size_t begin, size_t end);
	pair<size_t, size_t> snippet(
			const vector<Token> &tokens, size_t WIDTH);
public:
	Snippet(const map<string, double> &terms) : terms(terms) {}
	virtual string snippet(istream &in, size_t WIDTH=100, 
			const Analyzer &analyzer=Analyzer());
	virtual ~Snippet() {}
};


#endif
