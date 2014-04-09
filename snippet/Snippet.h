#ifndef _SNIPPET_H_
#define _SNIPPET_H_

#include <map>
#include <string>
#include <utility>
#include <Analyzer.h>

using namespace std;


class Snippet {
private:
	static pair<size_t, size_t> fetchSnippetPos(
			const map<string, double> &terms, istream &in, 
			size_t width, const Analyzer &analyzer);
public:
	static string snippet(const map<string, double> &terms, istream &in,
			size_t width=100, const Analyzer &analyzer=Analyzer());
};


#endif
