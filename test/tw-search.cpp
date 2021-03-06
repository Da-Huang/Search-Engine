#include <sstream>
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


static void twSearch(IndexSearcher &is, const string &qStr, bool fuzzy);

void twSearch(const string &indexPath, istream &in, bool fuzzy) {
	IndexSearcher is(indexPath);

	string line;
	while ( getline(in, line) ) {
		line = util::trim(line);
		if ( line.length() == 0 ) continue;
		cout << line << endl;
		twSearch(is, line, fuzzy);
	}
}	

void twSearch(const string &indexPath, const string &qStr, bool fuzzy) {
	IndexSearcher is(indexPath);
/*
	static bool isOut = true;
	if ( isOut )
		cout << is.toString() 
			<< "=======================================" << endl;
	isOut  = false;
*/
	twSearch(is, qStr, fuzzy);
}


void twSearch(IndexSearcher &is, const string &qStr, bool fuzzy) {

	string queryString = qStr;
	Analyzer analyzer;
	const Query *pQuery1 = QueryParser::parse(
			queryString,
			"body", 
			analyzer, fuzzy);
	Query *pQuery2 = QueryParser::parse(
			queryString,
			"title",
			analyzer, fuzzy);
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
