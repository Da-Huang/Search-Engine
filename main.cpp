#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <string>
#include "stemmer.h"

using namespace boost;
using namespace std;

int main() {
	string s;
	string line;
	while ( cin >> line ) {
		s += line;
		s += "\n";
	}
//	cout << s << endl;
	Stemmer stemmer;
	vector<string> sl = stemmer.tokenize(s);
	cout << "===============================" << endl;
	for (auto it = sl.begin(); it != sl.end(); it ++)
		cout << *it << endl;
	return 0;
}

