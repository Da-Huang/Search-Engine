#include <IndexSearcher.h>
#include <Query.h>
#include <TermQuery.h>
#include <QueryParser.h>
#include <FuzzyQuery.h>
#include <ScoreDoc.h>
#include <OrQuery.h>
#include <BoolAnalyzer.h>
#include <util.h>
#include <tinyxml2.h>
namespace test {
using namespace tinyxml2;


static void search(IndexSearcher &is, const string &qStr, bool fuzzy);

void search(const string &indexPath, istream &in, bool fuzzy) {
	IndexSearcher is(indexPath);

	string line;
	while ( getline(in, line) ) {
		line = util::trim(line);
		if ( line.length() == 0 ) continue;
		cout << line << endl;
		search(is, line, fuzzy);
	}
}	

void search(const string &indexPath, const string &qStr, bool fuzzy) {
	IndexSearcher is(indexPath);
/*
	static bool isOut = true;
	if ( isOut )
		cout << is.toString() 
			<< "=======================================" << endl;
	isOut  = false;
*/
	test::search(is, qStr, fuzzy);
}


void search(IndexSearcher &is, const string &qStr, bool fuzzy) {

	string queryString = qStr;
	Analyzer analyzer;
	const Query *pQuery1 = QueryParser::parse(
			queryString,
			"text", 
			analyzer, fuzzy);
	const Query *pQuery2 = QueryParser::parse(
			queryString,
			"title",
			analyzer, fuzzy);

	const Query *query = new OrQuery(*pQuery1, *pQuery2);

	cout << "Inner Query:  " << query->toString() << endl;
	
	vector<ScoreDoc> scoreDocs = is.search(*query);
	cout << "Hit Numbers:  " << scoreDocs.size() << endl;
	cout << "Hit Documents:" << endl;
	const size_t SHOW_NUM = 15;
	for (size_t i = 0; i < scoreDocs.size() && i < SHOW_NUM; i ++) {
		fprintf(stdout, "%4ld. #%-4ld ", i + 1, scoreDocs[i].id());
//		cout << is.doc(scoreDocs[i].id()).toString() << endl;
		string path = is.doc(scoreDocs[i].id()).get("filePath");
		cout << path << endl;

		XMLDocument xmlDoc;
		xmlDoc.LoadFile(path.c_str());
		XMLElement *newsitem = xmlDoc.RootElement();
		XMLElement *xmlTitle = newsitem ? 
			newsitem->FirstChildElement("title") : NULL;
		string title = xmlTitle && xmlTitle->GetText() ? 
			xmlTitle->GetText() : "";
		cout << "\t" << title << endl;
	}
	if ( scoreDocs.size() > SHOW_NUM )
		cout << "(There are more hit documents...)" << endl;
	delete query;
}


}
