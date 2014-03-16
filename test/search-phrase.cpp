#include <IndexSearcher.h>
#include <Query.h>
#include <TermQuery.h>
#include <QueryParser.h>
#include <FuzzyQuery.h>
#include <ScoreDoc.h>
#include <OrQuery.h>
#include <BoolAnalyzer.h>
#include <util.h>
namespace test {


static void searchPhrase(IndexSearcher &is, const string &qStr, bool fuzzy);

void searchPhrase(const string &indexPath, istream &in, bool fuzzy) {
	string indexPrefix = indexPath;
	indexPrefix += "/_";
	IndexSearcher is(indexPrefix);

	string line;
	while ( getline(in, line) ) {
		line = util::trim(line);
		if ( line.length() == 0 ) continue;
		searchPhrase(is, line, fuzzy);
	}
}	

void searchPhrase(const string &indexPath, const string &qStr, bool fuzzy) {

	string indexPrefix = indexPath;
	indexPrefix += "/_";
	IndexSearcher is(indexPrefix);
/*
	static bool isOut = true;
	if ( isOut )
		cout << is.toString() 
			<< "=======================================" << endl;
	isOut  = false;
*/
	test::searchPhrase(is, qStr, fuzzy);
}


void searchPhrase(IndexSearcher &is, const string &qStr, bool fuzzy) {

	string queryString = qStr;
	const Query *pQuery = QueryParser::parsePhrase(
			queryString,
			"content", 
			BoolAnalyzer(), fuzzy);
	const Query *tQuery = fuzzy ? 
		new FuzzyQuery("fileName", qStr) :
		new TermQuery("fileName", qStr);

	const Query *query = pQuery == NULL ? tQuery : 
		new OrQuery(*pQuery, *tQuery);

	cout << "Inner Query:  " << query->toString() << endl;
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
	cout << "Hit Numbers:  " << scoreDocs.size() << endl;
	cout << "Hit Documents:" << endl;
	for (size_t i = 0; i < scoreDocs.size(); i ++) {
		fprintf(stdout, "%4ld. #%4ld ", i + 1, scoreDocs[i].id());
		cout << is.doc(scoreDocs[i].id()).toString() << endl;
	}
	delete query;
}


}
