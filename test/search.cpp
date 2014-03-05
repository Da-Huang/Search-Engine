#include <KernelTest.h>
#include <IndexSearcher.h>
#include <Query.h>
#include <TermQuery.h>
#include <QueryParser.h>
#include <ScoreDoc.h>
#include <OrQuery.h>
#include <BoolAnalyzer.h>


void KernelTest::search(const string &indexPath, const string &qStr) {
	string indexPrefix = indexPath;
	indexPrefix += "/_";
	IndexSearcher is(indexPrefix);
//	cout << is.toString() 
//		<< "=======================================" << endl;

	const Query *bQuery = QueryParser::parseBool(
			qStr,
			"content", 
			BoolAnalyzer());

	const Query *tQuery = new TermQuery("fileName", qStr);
	const Query *query = new OrQuery(*bQuery, *tQuery);

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


