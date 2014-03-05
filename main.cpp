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
#include <NotQuery.h>
#include <AndQuery.h>
#include <OrQuery.h>
#include <ScoreDoc.h>

using namespace std;


istream &get(const string &str) {
	static istringstream istr(str);
	istream &t = istr;
	return t;
}

vector<vector<string>> tests = {
	{"This is a good day!", "", "It is a hot day.", "Hot day Today."},
	{"OK", "Today is a cold day.", "", "My day is a happy day."},
	{"BAD", "", "This is a test.", ""},
	{"USEFUL", "", "This goes right.", "The day comes."},
	{"SHIT", "", "", "It goes right this day."},
};


int main() {
	
/*
	IndexWriter iw("/home/dhuang/index");
	Analyzer analyzer;
	for (size_t i = 0; i < tests.size(); i ++) {
		StringField field0 = StringField("title", tests[i][0]);
		Document doc = Document();
		doc.addField(field0);
		for (size_t j = 1; j < tests[i].size(); j ++) {
			doc.addField(
					*new TextField(string(1, 'a' + j - 1), tests[i][j], analyzer));
		}
		iw.write(doc);
	}
	cout << iw.toString() << endl << endl;
	iw.close();

	*/

	IndexSearcher is("/home/dhuang/index/_");
	cout << is.toString() 
		<< "=======================================" << endl;

//	Query *query = new NotQuery(TermQuery("c", "day"));
	/*
	const Query &tq = TermQuery("c", "day");
	const Query &nq = NotQuery(tq);
	const Query &nnq = NotQuery(nq);
	cerr << nnq.toString() << endl;
	*/
	const Query &q = *new NotQuery(*new NotQuery(
			*new NotQuery(
				*new TermQuery("c", "day")
			)
		));

	cerr << q.toString() << endl;
	delete &q;
//	cerr << tq.toString() << endl;
//	cerr << nq.toString() << endl;
//	cerr << q.toString() << endl;
/*	
	vector<ScoreDoc> scoreDocs = is.search(NotQuery(TermQuery("c", "day")));
	for (auto it = scoreDocs.begin(); it != scoreDocs.end(); it ++) {
		cout << it->id() << "." << is.doc(it->id()).toString() << endl;
	}
	cerr << "OK" << endl;
	
*/
	return 0;
}


