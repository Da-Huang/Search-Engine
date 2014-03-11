#include <iostream>
#include <test.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;


static const vector<string> usages = {
	"usage: -index \"data directory\" \"index directory\"",
	"usage: -search-bool \"index directory\" \"query string\"",
	"usage: -search-bool-batch \"index directory\" \"query file\"",
	"usage: -search-phrase \"index diectory\" \"query string\"",
	"usage: -search-phrase-batch \"index directory\" \"query file\"",
};


int main(int argc, char* argv[]) {
	
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

		} else if ( string(argv[i]) == "-search-bool-batch" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[2] << endl;
				return -1;
			}
			ifstream in(argv[i + 2]);
			test::searchBool(string(argv[i + 1]), in);
			in.close();
			return 0;

		} else if ( string(argv[i]) == "-search-phrase" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[3] << endl;
				return -1;
			}
			test::searchPhrase(string(argv[i + 1]), string(argv[i + 2]));
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
		}
	}

	for (size_t i = 0; i < usages.size(); i ++)
		cerr << usages[i] << endl;
	
//	test::index("/media/DISK_D/input", "/home/dhuang/index");

//	test::searchPhrase("/home/dhuang/index", "brutus ~4~ caesar");
//	test::searchPhrase("/home/dhuang/index", argv[1]);

	return -1;
}


