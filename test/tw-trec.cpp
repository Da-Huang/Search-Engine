#include <sstream>
#include <cassert>
#include <XMLDoc.h>
#include <IndexSearcher.h>
#include <Query.h>
#include <TermQuery.h>
#include <QueryParser.h>
#include <FuzzyQuery.h>
#include <ScoreDoc.h>
#include <AndQuery.h>
#include <OrQuery.h>
#include <XMLDoc.h>
#include <BoolAnalyzer.h>
#include <Snippet.h>
#include <util.h>
#include <test.h>
namespace test {


bool nextNumber(istream &in, size_t &number);
string nextTitle(istream &in);
static void twTrec(IndexSearcher &is, const string &qStr, size_t number);


void twTrec(const string &indexPath, istream &in) {
	IndexSearcher is(indexPath);

	size_t number;
	while ( nextNumber(in, number) ) {
		string title = nextTitle(in);
		twTrec(is, title, number);
	}
}	

void twTrec(IndexSearcher &is, const string &qStr, size_t number) {

	string queryString = qStr;
	Analyzer analyzer;
	const Query *pQuery1 = QueryParser::parse(
			queryString,
			"body", 
			analyzer, false);
	Query *pQuery2 = QueryParser::parse(
			queryString,
			"title",
			analyzer, false);
	pQuery2->setBoost(10);

	const Query *query = new OrQuery(*pQuery1, *pQuery2);
	cout << "Inner Query:  " << query->toString() << endl;

	map<string, double> scoreTerms = pQuery1->fetchScoreTerms(is);
	Snippet snippet(scoreTerms);
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
	cout << "Hit Numbers:  " << scoreDocs.size() << endl;
	cout << "Hit Documents:" << endl;
	const size_t SHOW_NUM = 15;
	for (size_t i = 0; i < scoreDocs.size() && i < SHOW_NUM; i ++) {
//		cout << is.doc(scoreDocs[i].id()).toString() << endl;
		Document doc = is.doc(scoreDocs[i].id());
		string path = doc.get("path");
		size_t offset = stol(doc.get("offset"));

		ifstream in(path);
		in.seekg(offset);
		map<string, string> record = twConvert(in);
		in.close();

		fprintf(stdout, "%4ld. %s ", i + 1, record["trecid"].c_str());
		cout << record["title"] << endl;
		cout << "\t" << scoreDocs[i].score() << endl;

		istringstream istr(record["body"]);
		cout << "\t" << snippet.snippet(istr) << endl;
	}
	if ( scoreDocs.size() > SHOW_NUM )
		cout << "(There are more hit documents...)" << endl;
	delete query;
}


}
