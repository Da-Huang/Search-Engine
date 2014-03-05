#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <StringField.h>
#include <TextField.h>
#include <Document.h>
#include <TokenStream.h>
#include <IndexWriter.h>
#include <FileIndex.h>
#include <IndexSearcher.h>
#include <DocDB.h>
#include <TermQuery.h>
#include <BoolAnalyzer.h>
#include <NotQuery.h>
#include <AndQuery.h>
#include <OrQuery.h>
#include <ScoreDoc.h>
#include <QueryParser.h>
#include <KernelTest.h>

using namespace std;


istream &get(const string &str) {
	static istringstream istr(str);
	istream &t = istr;
	return t;
}


int main() {
//	KernelTest::index("/media/DISK_D/input", "/home/dhuang/index");


	IndexSearcher is("/home/dhuang/index/_");
//	cout << is.toString() 
//		<< "=======================================" << endl;
//	Query *query = new NotQuery(TermQuery("c", "day"));

	const Query *query = QueryParser::parseBool(
//			"( calpurnia & brutus & caesar ) ",
//			"ignoble | strife",
//			"macbeth | exeunt",
//			"crowd | madding",
//			"( ( ignoble | strife ) & ( crowd | madding ) & ( slain | killed ) ) ",
//			"( ( brutus | caesar ) & ! calpurnia )",
//			"brutus | caesar",
//			"( brutus | caesar ) & ! calpurnia",
//			"brutus & caesar & calpurnia",
//			"! calpurnia",
//			"caesar",
			"content", 
			BoolAnalyzer());
	cout << query->toString() << endl;
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
	cout << scoreDocs.size() << endl;
	for (auto it = scoreDocs.begin(); it != scoreDocs.end(); it ++) {
		cout << it->id() << "." << is.doc(it->id()).toString() << endl;
	}
	
	delete query;
	return 0;
}


