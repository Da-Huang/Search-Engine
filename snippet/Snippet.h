#ifndef _SNIPPET_H_
#define _SNIPPET_H_

#include <map>
#include <string>
#include <Analyzer.h>

using namespace std;


class Snippet {
public:
	static string snippet(map<string, double> terms, istream &in,
			const Analyzer &analyzer=Analyzer());
};


#endif
