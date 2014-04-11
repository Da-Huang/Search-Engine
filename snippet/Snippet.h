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
	static pair<size_t, size_t> snippet(const map<string, double> &terms,
			const vector<Token> &tokens, size_t WIDTH);
	static string fetch(istream &in, size_t begin, size_t end);
public:
	static string snippet(const map<string, double> &terms, istream &in,
			size_t WIDTH=100, const Analyzer &analyzer=Analyzer());
};


#endif
