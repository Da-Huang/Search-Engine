#include <util.h>
#include <Query.h>
#include <TermQuery.h>
#include <QueryParser.h>
#include <FuzzyQuery.h>
#include <ScoreDoc.h>
#include <OrQuery.h>
#include <IndexSearcher.h>
#include <BoolAnalyzer.h>
#include <tinyxml2.h>
namespace test {
using namespace tinyxml2;


static void searchBool(IndexSearcher &is, const string &qStr, bool fuzzy);

void searchBool(const string &indexPath, istream &in, bool fuzzy) {
	IndexSearcher is(indexPath);

	string line;
	while ( getline(in, line, '\n') ) {
		line = util::trim(line);
		if ( line.length() == 0 ) continue;
		cout << line << endl;
		searchBool(is, line, fuzzy);
	}
}	

void searchBool(const string &indexPath, const string &qStr, bool fuzzy) {
	IndexSearcher is(indexPath);
/*
	static bool isOut = true;
	if ( isOut )
		cout << is.toString() 
			<< "=======================================" << endl;
	isOut  = false;
*/
	searchBool(is, qStr, fuzzy);
}

void searchBool(IndexSearcher &is, const string &qStr, bool fuzzy) {
	string queryString;
	for (size_t i = 0; i < qStr.length(); i ++) {
		if ( qStr[i] == '(' || qStr[i] == ')' || qStr[i] == '|' ||
				qStr[i] == '&' || qStr[i] == '!' ) {
			queryString.push_back(' ');
			queryString.push_back(qStr[i]);
			queryString.push_back(' ');

		} else queryString.push_back(qStr[i]);
	}
	const Query *bQuery1 = QueryParser::parseBool(
			queryString,
			"text", 
			BoolAnalyzer(), fuzzy);
	Query *bQuery2 = QueryParser::parseBool(
			queryString,
			"title", 
			BoolAnalyzer(), fuzzy);
	bQuery2->setBoost(10);

	const Query *query = new OrQuery(*bQuery1, *bQuery2);
	cout << "Inner Query:  " << query->toString() << endl;
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
	cout << "Hit Numbers:  " << scoreDocs.size() << endl;
	cout << "Hit Documents:" << endl;
	for (size_t i = 0; i < scoreDocs.size(); i ++) {
		fprintf(stdout, "%4ld. #%-4ld ", i + 1, scoreDocs[i].id());
		Document doc = is.doc(scoreDocs[i].id());
		cout << doc.get("filePath") << endl;
/*
		XMLDocument xmlDoc;
		xmlDoc.LoadFile(doc.get("filePath").c_str());
		XMLElement *newsitem = xmlDoc.RootElement();
		XMLElement *title = newsitem->FirstChildElement("title");
		cout << "\t" << title->GetText() << endl;
*/
//		cout << is.doc(scoreDocs[i].id()).toString() << endl;
	}
	delete query;
}


}
