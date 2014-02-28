#include <iostream>
#include <sstream>
#include <vector>
#include <boost/regex.hpp>
#include <string>
#include "Stemmer.h"
#include "index/field/StringField.h"

using namespace boost;
using namespace std;

istream &get(const string &str) {
	static istringstream istr(str);
	istream &t = istr;
	return t;
}

int main() {
//	Field f = Str
	/*
	StringField("abc", "efg");
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
		*/

	string s = "shit";
//	istringstream istr = 
	istream &in = get(s);
	cout << in;
	string t;
	while ( getline(in, t) ) {
		cout << t << endl;
	}
	return 0;
}


