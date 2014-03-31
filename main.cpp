#include <iostream>
#include <test.h>
#include <vector>
#include <fstream>
#include <cassert>
#include <Analyzer.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int run(int argc, char* argv[]);

#include <util.h>
#include <TermQuery.h>
#include <ScoreDoc.h>
#include <IndexSearcher.h>
#include <AndQuery.h>
#include <tinyxml2.h>
#include <TmpPostingStream.h>
#include <MMIndex.h>
using namespace tinyxml2;
int main(int argc, char* argv[]) {
//	map<string, map<size_t, vector<Posting>>> m;
//	vector<Posting> &pl = m["go"][0];
//	MMIndex mm;
//	mm.add("go", 1, 2, 3);
//	cout << mm.toString() << endl;

//	return 0;
	return run(argc, argv);
//	test::littleIndex();
//	return 0;

	IndexSearcher is("../index2");
	cout << is.toString() << endl;
	return 0;
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

//	test::index("/media/DISK_D/input", "/home/dhuang/index");

//	test::searchPhrase("/home/dhuang/index", "brutus ~4~ caesar");
//	test::searchPhrase("/home/dhuang/index", argv[1]);
}


