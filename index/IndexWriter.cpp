#include <IndexWriter.h>
#include <cstdlib>

using namespace std;

IndexWriter::IndexWriter(const string &dirPath) 
	: dirPath(dirPath), currentDocID(0) {
	string cmd = "mkdir -p ";
	cmd += dirPath;
	system(cmd.c_str());
}

void IndexWriter::write(Document &doc) {
	for (auto it = doc.fields.begin(); it != doc.fields.end(); it ++) {
		Field& field = it->second;
		field.writeTo(mmIndex, currentDocID);
	}
}

void IndexWriter::merge() {
	string cmd = "mv ";
	cmd += dirPath;
	cmd += "/__1.trm ";
	cmd += dirPath;
	cmd += "/_.trm";
	system(cmd.c_str());

	cmd = "mv ";
	cmd += dirPath;
	cmd += "/__1.idx ";
	cmd += dirPath;
	cmd += "/_.idx";
	system(cmd.c_str());

	cmd = "mv ";
	cmd += dirPath;
	cmd += "/__1.fld ";
	cmd += dirPath;
	cmd += "/_.fld";
	system(cmd.c_str());
}

void IndexWriter::close() {
	merge();
	string cmd = "rm -f ";
	cmd += dirPath;
	cmd += "/__*";
	system(cmd.c_str());
}

