#include <iostream>
#include <KernelTest.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;


static const vector<string> usages = {
	"usage: -index \"data directory\" \"index directory\"",
	"usage: -search \"index directory\" \"query string\"",
};


int main(int argc, char* argv[]) {
	/*
	int i = 1;
	for (i = 1; i < argc; i ++) {
		if ( string(argv[i]) == "-index" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[0] << endl;
				return -1;
			}
			KernelTest::index(string(argv[i + 1]), string(argv[i + 2]));
			cout << "Finish Indexing. You can search now." << endl;
			return 0;

		} else if ( string(argv[i]) == "-search" ) {
			if ( i + 2 >= argc ) {
				cerr << usages[1] << endl;
				return -1;
			}
			KernelTest::search(string(argv[i + 1]), string(argv[i + 2]));
			return 0;

		}
	}

	for (size_t i = 0; i < usages.size(); i ++)
		cerr << usages[i] << endl;
	*/
	
	
	
	KernelTest::index("/media/DISK_D/input", "/home/dhuang/index");

	KernelTest::search("/home/dhuang/index", "((brutus | caesar) & ! calpurnia)");
	KernelTest::search("/home/dhuang/index", "((brutus & (caesar & calpurnia))");
	KernelTest::search("/home/dhuang/index", "((madding | crowd) & (ignoble | strife) & (killed | slain))");
	KernelTest::search("/home/dhuang/index", "! calpurnia");
	KernelTest::search("/home/dhuang/index", "brutus");
	
	KernelTest::search("/home/dhuang/index", "caesar");
	
	KernelTest::search("/home/dhuang/index", "! brutus & ! caesar");
	KernelTest::search("/home/dhuang/index", "brutus | caesar");
	KernelTest::search("/home/dhuang/index", "README");
	

	return -1;
}


