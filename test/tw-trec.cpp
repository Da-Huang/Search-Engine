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
//	cerr << "Inner Query:  " << query->toString() << endl;

	map<string, double> scoreTerms = pQuery1->fetchScoreTerms(is);
	Snippet snippet(scoreTerms);
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
//	cerr << "Hit Numbers:  " << scoreDocs.size() << endl;
//	cerr << "Hit Documents:" << endl;
	static const size_t SHOW_NUM = 1000;
	for (size_t i = 0; i < scoreDocs.size() && i < SHOW_NUM; i ++) {
		Document doc = is.doc(scoreDocs[i].id());
		string path = doc.get("path");
		size_t offset = stol(doc.get("offset"));

		ifstream in(path);
		in.seekg(offset);
		map<string, string> record = twConvert(in);
		in.close();

		cout << number << " ";					// qid
		cout << "Q0" << " ";					// iter : set as Q0
		cout << record["trecid"] << " ";		// docno
		cout << i + 1 << " ";					// rank
		cout << scoreDocs[i].score() << " ";	// sim
		cout << "prise1" << endl;				// runid
/*
		fprintf(stderr, "%4ld. %s ", i + 1, record["trecid"].c_str());
		cerr << record["title"] << endl;
		cerr << "\t" << scoreDocs[i].score() << endl;

		istringstream istr(record["body"]);
		cerr << "\t" << snippet.snippet(istr) << endl;
*/
	}
//	if ( scoreDocs.size() > SHOW_NUM )
//		cerr << "(There are more hit documents...)" << endl;
	delete query;
}


}
