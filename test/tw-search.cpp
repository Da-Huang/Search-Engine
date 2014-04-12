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
			"text", 
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
		fprintf(stdout, "%4ld. #%-4ld ", i + 1, scoreDocs[i].id());
//		cout << is.doc(scoreDocs[i].id()).toString() << endl;
		string path = is.doc(scoreDocs[i].id()).get("filePath");
		cout << path << endl;

		XMLDoc xmlDoc(path);
		cout << "\t" << xmlDoc.getTitle() << endl;
		cout << "\t" << scoreDocs[i].score() << endl;

		istringstream istr(xmlDoc.getText());
		cout << "\t" << snippet.snippet(istr) << endl;
	}
	if ( scoreDocs.size() > SHOW_NUM )
		cout << "(There are more hit documents...)" << endl;
	delete query;
}


}
