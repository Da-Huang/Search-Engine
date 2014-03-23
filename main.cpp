#include <iostream>
#include <test.h>
#include <vector>
#include <fstream>
#include <cassert>
#include <Analyzer.h>
#include <string.h>
#include <unistd.h>

using namespace std;


static const vector<string> usages = {
	"usage: -index \"data directory\" \"index directory\"",
	"usage: -search-bool \"index directory\" \"query string\"",
	"usage: -search-bool-f \"index directory\" \"query string\"",
	"usage: -search-bool-batch \"index directory\" \"query file\"",
	"usage: -search-bool-f-batch \"index directory\" \"query file\"",
	"usage: -search-phrase \"index diectory\" \"query string\"",
	"usage: -search-phrase-f \"index diectory\" \"query string\"",
	"usage: -search-phrase-batch \"index directory\" \"query file\"",
	"usage: -search-phrase-f-batch \"index directory\" \"query file\"",
	"usage: -search \"index directory\" \"query string\"",
	"usage: -search-f \"index directory\" \"query file\"",
};

int run(int argc, char* argv[]) {
	int i = 1;
	for (i = 1; i < argc; i ++) {
		if ( string(argv[i]) == "-index" ) {
			assert (i + 2 < argc);
			test::index(string(argv[i + 1]), string(argv[i + 2]));
			cout << "Finish Indexing. You can search now." << endl;
			return 0;

		} else if ( string(argv[i]) == "-search-bool" ) {
			assert (i + 2 < argc);
			test::searchBool(string(argv[i + 1]), string(argv[i + 2]));
			return 0;

		} else if ( string(argv[i]) == "-search-bool-f" ) {
			assert (i + 2 < argc);
			test::searchBool(
					string(argv[i + 1]), string(argv[i + 2]), true);
			return 0;

		} else if ( string(argv[i]) == "-search-bool-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::searchBool(string(argv[i + 1]), in);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-bool-f-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::searchBool(string(argv[i + 1]), in, true);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-phrase" ) {
			assert (i + 2 < argc);
			test::searchPhrase(string(argv[i + 1]), string(argv[i + 2]));
			return 0;

		} else if ( string(argv[i]) == "-search-phrase-f" ) {
			assert (i + 2 < argc);
			test::searchPhrase(
					string(argv[i + 1]), string(argv[i + 2]), true);
			return 0;

		} else if ( string(argv[i]) == "-search-phrase-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::searchPhrase(string(argv[i + 1]), in);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-phrase-f-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::searchPhrase(string(argv[i + 1]), in, true);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search" ) {
			assert (i + 2 < argc);
			test::search(string(argv[i + 1]), string(argv[i + 2]));
			return 0;

		} else if ( string(argv[i]) == "-search-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::search(string(argv[i + 1]), in);
			in.close();
			return 0;
		}
	}

	for (size_t i = 0; i < usages.size(); i ++)
		cerr << usages[i] << endl;
	return -1;
}

#include <util.h>
#include <FuzzyQuery.h>
#include <ScoreDoc.h>
#include <IndexSearcher.h>
#include <AndQuery.h>
#include <tinyxml2.h>
using namespace tinyxml2;
int main(int argc, char* argv[]) {
	
	return run(argc, argv);
//	test::littleIndex();
//	return 0;

	IndexSearcher is("../index/_");
//	FuzzyQuery fq("content", util::stem("caeassr"));
//	cout << fq.toString() << endl;

	/*
	TermQuery t1("content", util::stem("brutus"));
	TermQuery t2("content", util::stem("caesar"));
	*/
	TermQuery t3("text", util::stem("the"));
/*
	FuzzyQuery t1("content", "brutus");
	FuzzyQuery t2("content", "caessar");
	FuzzyQuery t3("content", "calpturniag");
	AndQuery aq(t1, t2);
	aq.add(t3);
	cout << aq.toString() << endl;
	*/

	vector<ScoreDoc> res = is.search(t3);
	for (size_t i = 0; i < res.size(); i ++) {
		printf("%4ld. #%-4ld ", i + 1, res[i].id());
		cout << is.doc(res[i].id()).toString() << endl;
	}


	
//	return run(argc, argv);
	
//	test::index("/media/DISK_D/input", "/home/dhuang/index");

//	test::searchPhrase("/home/dhuang/index", "brutus ~4~ caesar");
//	test::searchPhrase("/home/dhuang/index", argv[1]);
}


