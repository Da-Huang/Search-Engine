#include <IndexWriter.h>
#include <cstdlib>

using namespace std;

IndexWriter::IndexWriter(const string &dirPath) : dirPath(dirPath) {
	string cmd = "mkdir -p ";
	cmd += dirPath;
	system(cmd.c_str());
}

void IndexWriter::write(Document &doc) {
}


void IndexWriter::close() {
}


