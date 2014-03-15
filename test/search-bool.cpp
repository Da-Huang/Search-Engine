#include <IndexSearcher.h>
#include <Query.h>
#include <TermQuery.h>
#include <QueryParser.h>
#include <ScoreDoc.h>
#include <OrQuery.h>
#include <BoolAnalyzer.h>
#include <util.h>
namespace test {

static void searchBool(IndexSearcher &is, const string &qStr);

void searchBool(const string &indexPath, istream &in) {
	string indexPrefix = indexPath;
	indexPrefix += "/_";
	IndexSearcher is(indexPrefix);

	string line;
	while ( getline(in, line, '\n') ) {
		line = util::trim(line);
		if ( line.length() == 0 ) continue;
		cout << line << endl;
		searchBool(is, line);
	}
}	

void searchBool(const string &indexPath, const string &qStr) {
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
	test::searchBool(is, qStr);
}

void searchBool(IndexSearcher &is, const string &qStr) {
	string queryString;
	for (size_t i = 0; i < qStr.length(); i ++) {
		if ( qStr[i] == '(' || qStr[i] == ')' || qStr[i] == '|' ||
				qStr[i] == '&' || qStr[i] == '!' ) {
			queryString.push_back(' ');
			queryString.push_back(qStr[i]);
			queryString.push_back(' ');

		} else queryString.push_back(qStr[i]);
	}
	const Query *bQuery = QueryParser::parseBool(
			queryString,
			"content", 
			BoolAnalyzer());
	const Query *tQuery = new TermQuery("fileName", qStr);

	const Query *query = bQuery == NULL ? tQuery : 
		new OrQuery(*bQuery, *tQuery);

	cout << "Inner Query:  " << query->toString() << endl;
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
	cout << "Hit Numbers:  " << scoreDocs.size() << endl;
	cout << "Hit Documents:" << endl;
	for (size_t i = 0; i < scoreDocs.size(); i ++) {
		fprintf(stdout, "%4ld. ", i + 1);
		cout << is.doc(scoreDocs[i].id()).toString() << endl;
	}
	delete query;
}


}