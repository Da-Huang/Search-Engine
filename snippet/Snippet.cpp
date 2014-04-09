#include <Snippet.h>


string Snippet::snippet(map<string, double> terms, istream &in, 
		const Analyzer &analyzer) {
	string res;
	string line;
	while ( getline(in, line) ) {
		res += line;
	}
	return res;
}


