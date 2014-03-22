#include <iostream>
#include <test.h>
#include <vector>
#include <fstream>
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
};

int run(int argc, char* argv[]) {
	int i = 1;
	for (i = 1; i < argc; i ++) {
		if ( string(argv[i]) == "-index" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[0] << endl;
				return -1;
			}
			test::index(string(argv[i + 1]), string(argv[i + 2]));
			cout << "Finish Indexing. You can search now." << endl;
			return 0;

		} else if ( string(argv[i]) == "-search-bool" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[1] << endl;
				return -1;
			}
			test::searchBool(string(argv[i + 1]), string(argv[i + 2]));
			return 0;

		} else if ( string(argv[i]) == "-search-bool-f" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[1] << endl;
				return -1;
			}
			test::searchBool(
					string(argv[i + 1]), string(argv[i + 2]), true);
			return 0;

		} else if ( string(argv[i]) == "-search-bool-batch" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[2] << endl;
				return -1;
			}
			ifstream in(argv[i + 2]);
			test::searchBool(string(argv[i + 1]), in);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-bool-f-batch" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[2] << endl;
				return -1;
			}
			ifstream in(argv[i + 2]);
			test::searchBool(string(argv[i + 1]), in, true);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-phrase" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[3] << endl;
				return -1;
			}
			test::searchPhrase(string(argv[i + 1]), string(argv[i + 2]));
			return 0;

		} else if ( string(argv[i]) == "-search-phrase-f" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[3] << endl;
				return -1;
			}
			test::searchPhrase(
					string(argv[i + 1]), string(argv[i + 2]), true);
			return 0;

		} else if ( string(argv[i]) == "-search-phrase-batch" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[4] << endl;
				return -1;
			}
			ifstream in(argv[i + 2]);
			test::searchPhrase(string(argv[i + 1]), in);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-phrase-f-batch" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[4] << endl;
				return -1;
			}
			ifstream in(argv[i + 2]);
			test::searchPhrase(string(argv[i + 1]), in, true);
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

	XMLDocument doc;  
	doc.LoadFile("test.xml");  
	XMLElement *newsitem = doc.RootElement();
	XMLElement *text = newsitem->FirstChildElement("text");  
	XMLElement *p = text->FirstChildElement("p");
	while ( p ) {
		cout << p->GetText() << endl;
		p = p->NextSiblingElement();
	}
	return 0;

	IndexSearcher is("../index/_");
//	FuzzyQuery fq("content", util::stem("caeassr"));
//	cout << fq.toString() << endl;

	/*
	TermQuery t1("content", util::stem("brutus"));
	TermQuery t2("content", util::stem("caesar"));
	TermQuery t3("content", util::stem("calpurnia"));
	*/

	FuzzyQuery t1("content", "brutus");
	FuzzyQuery t2("content", "caessar");
	FuzzyQuery t3("content", "calpturniag");
	AndQuery aq(t1, t2);
	aq.add(t3);
	cout << aq.toString() << endl;

	vector<ScoreDoc> res = is.search(aq);
	for (size_t i = 0; i < res.size(); i ++) {
		cout << is.doc(res[i].id()).toString() << endl;
	}


	
//	return run(argc, argv);
	
//	test::index("/media/DISK_D/input", "/home/dhuang/index");

//	test::searchPhrase("/home/dhuang/index", "brutus ~4~ caesar");
//	test::searchPhrase("/home/dhuang/index", argv[1]);
}


