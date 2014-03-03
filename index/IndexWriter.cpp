#include <IndexWriter.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

IndexWriter::IndexWriter(const string &dirPath) : dirPath(dirPath) {
//	string path = dirPath;
	mkdir(dirPath.c_str(), (mode_t)0x775);
}

void IndexWriter::write(Document &doc) {
}


void IndexWriter::close() {
}


