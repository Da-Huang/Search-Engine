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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
using namespace boost::property_tree;

int main() {
	ptree pt;
	pt.put("field.fields", 1);
	ofstream out("test.ini");
	write_ini(out, pt);
	out.close();
	/*
	Analyzer analyzer;
	Document doc;
	StringField f1("abc", "efg");
	TextField f2("text", "text2", analyzer);
	doc.addField(f1);
	doc.addField(f2);
	cout << doc.toString() << endl;
	*/

	return 0;
}


