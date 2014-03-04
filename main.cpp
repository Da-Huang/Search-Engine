#include <iostream>
#include <sstream>
#include <vector>
//#include <boost/regex.hpp>
#include <string>
#include <StringField.h>
#include <TextField.h>
#include <Document.h>
#include <IndexWriter.h>
#include <FileIndex.h>
#include <DocDB.h>

//using namespace boost;
using namespace std;


istream &get(const string &str) {
	static istringstream istr(str);
	istream &t = istr;
	return t;
}

#include <TokenStream.h>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/ini_parser.hpp>
//using namespace boost::property_tree;


int main() {
	/*
	ptree pt;
	pt.put("field fields", 1);
	ofstream out("test.ini");
	write_ini(out, pt);
	out.close();
	*/
	
/*
	IndexWriter iw("/home/dhuang/index");
	Analyzer analyzer;
	for (int i = 0; i < 5; i ++) {
		TextField field1 = TextField("a", "This is a good day!", analyzer);
		StringField field2 = StringField("b", "good");
		Document doc = Document();
		doc.addField(field1);
		doc.addField(field2);
		iw.write(doc);
	}
	iw.close();
*/

//	doc.~Document();
	
	
	FileIndex fidx("/home/dhuang/index/_", sizeof(size_t) * 5);
	for (size_t i = 1; i <= fidx.getTermNum(); i ++) {
		cout << fidx.fetchTerm(i) << endl;
	}
	FieldNameMap fieldNameMap;
	ifstream fldIn("/home/dhuang/index/_.fld");
	fieldNameMap.load(fldIn);
	cout << fieldNameMap.toString() << endl;;
	DocDB docDB("/home/dhuang/index/_", fieldNameMap);
	for (size_t i = 1; i <= docDB.getDocNum(); i ++) {
		Document doc = docDB.fetchDocument(i);
		cout << doc.toString() << endl;
	}

	fldIn.close();

	return 0;
}


