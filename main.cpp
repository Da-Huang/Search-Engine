#include <iostream>
#include <sstream>
#include <vector>
//#include <boost/regex.hpp>
#include <string>
#include <StringField.h>
#include <TextField.h>
#include <Document.h>
#include <IndexWriter.h>

//using namespace boost;
using namespace std;


istream &get(const string &str) {
	static istringstream istr(str);
	istream &t = istr;
	return t;
}

#include <TokenStream.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
using namespace boost::property_tree;

int main() {
	/*
	ptree pt;
	pt.put("field fields", 1);
	ofstream out("test.ini");
	write_ini(out, pt);
	out.close();
	*/
	IndexWriter iw("/home/dhuang/index");
	StringField field = StringField("a", "a");
	Document doc = Document();
	doc.addField(field);
	iw.write(doc);
	iw.close();


	return 0;
}


