#include <iostream>

using namespace std;


int run(int argc, char* argv[]);

#include <sstream>
#include <Snippet.h>
int main(int argc, char* argv[]) {
//	return run(argc, argv);
	map<string, double> terms;
	terms["big"] = 0.8;
	terms["plai"] = 1;
	terms["hello"] = 1.3;

	string str = "This is a good day, and my \nmind is clear today. The most happiest thing is that I'm   hello begining to \t test hello a great snippet algorithm.  That is  \n it. Thank you for attention. Ladies and gentlemen,\n I'm so graful today. Let's have big some fun today play.";
	istringstream is(str);
	Snippet snippet(terms);
	string s = snippet.snippet(is);
	cout << s << endl;

	return 0;
}


