#include <IndexWriter.h>
#include <cstdlib>

using namespace std;

IndexWriter::IndexWriter(const string &dirPath) : dirPath(dirPath) {
	string cmd = "mkdir -p ";
	cmd += dirPath;
	system(cmd.c_str());
}

void IndexWriter::write(Document &doc) {
	
	for (auto it = doc.fields.begin(); 
			it != doc.fields.end(); it ++) {
//		mmIndex.add(it->first, );
	}
}

void IndexWriter::merge() {
}

void IndexWriter::close() {
	merge();
	string cmd = "rm -f ";
	cmd += dirPath;
	cmd += "/__*";
	system(cmd.c_str());
}

