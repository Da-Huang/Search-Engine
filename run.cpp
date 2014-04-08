#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <test.h>

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
	"usage: -search-f \"index directory\" \"query string\"",
	"usage: -search-batch \"index directory\" \"query file\"",
	"usage: -search-f-batch \"index directory\" \"query file\"",
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

		} else if ( string(argv[i]) == "-search-f" ) {
			assert (i + 2 < argc);
			test::search(string(argv[i + 1]), string(argv[i + 2]), true);
			return 0;

		} else if ( string(argv[i]) == "-search-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::search(string(argv[i + 1]), in);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-f-batch" ) {
			assert (i + 2 < argc);
			ifstream in(argv[i + 2]);
			test::search(string(argv[i + 1]), in, true);
			in.close();
			return 0;
		}
	}

	for (size_t i = 0; i < usages.size(); i ++)
		cerr << usages[i] << endl;
	return -1;
}


