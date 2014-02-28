#include <iostream>
#include <sstream>
#include <vector>
//#include <boost/regex.hpp>
#include <string>
#include "Stemmer.h"
#include "index/field/StringField.h"
#include "index/field/TextField.h"
#include "index/Document.h"

//using namespace boost;
using namespace std;


istream &get(const string &str) {
	static istringstream istr(str);
	istream &t = istr;
	return t;
}


int main() {
	Analyzer analyzer;
	Document doc;
	StringField f1("abc", "efg");
	TextField f2("text", "text2", analyzer);
	doc.addField(f1);
	doc.addField(f2);
	cout << doc.toString() << endl;

	return 0;
}


