#include <iostream>
#include <cstdlib>
#include <fstream>
#include <IndexWriter.h>

using namespace std;

void IndexWriter::addField(const string &field) {
	auto it = fieldIDMap.find(field);
	if ( it != fieldIDMap.end() ) return;
	fieldIDMap[field] = fields.size();
	fields.push_back(field);
}

IndexWriter::IndexWriter(const string &dirPath) 
	: dirPath(dirPath), currentDocID(0) {
	string cmd = "mkdir -p ";
	cmd += dirPath;
	system(cmd.c_str());
}

void IndexWriter::write(Document &doc) {
	for (auto it = doc.fields.begin(); it != doc.fields.end(); it ++) {
		Field& field = it->second;
		addField(field.getFieldName());
		field.writeTo(mmIndex, fieldIDMap, currentDocID);
	}
//	cerr << mmIndex.toString() << endl;
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

	cmd = "mv ";
	cmd += dirPath;
	cmd += "/__1.pst ";
	cmd += dirPath;
	cmd += "/_.pst";
	system(cmd.c_str());
}

void IndexWriter::close() {
	string idxPath = dirPath;
	idxPath += "/__1.idx";
	string fldPath = dirPath;
	fldPath += "/__1.fld";
	string trmPath = dirPath;
	trmPath += "/__1.trm";
	string pstPath = dirPath;
	pstPath += "/__1.pst";

	ofstream idxOut(idxPath);
	ofstream fldOut(fldPath);
	ofstream trmOut(trmPath);
	ofstream pstOut(pstPath);

	mmIndex.writeTo(idxOut, fldOut, trmOut, pstOut, fields.size());

	idxOut.close();
	fldOut.close();
	trmOut.close();
	pstOut.close();

	merge();
	string cmd = "rm -f ";
	cmd += dirPath;
	cmd += "/__*";
	system(cmd.c_str());
}


