#include <iostream>
#include <cstdlib>
#include <fstream>
#include <StringField.h>
#include <IndexWriter.h>

using namespace std;

void IndexWriter::addFieldName(const string &fieldName) {
	fieldNameMap.addFieldName(fieldName);
}

IndexWriter::IndexWriter(const string &dirPath) 
	: dirPath(dirPath), currentDocID(1) {
	string cmd = "mkdir -p ";
	cmd += dirPath;
	system(cmd.c_str());

	string docPath = dirPath;
	docPath += "/_.doc";
	string cntPath = dirPath;
	cntPath += "/_.cnt";

	docOut.open(docPath);
	cntOut.open(cntPath);
}

void IndexWriter::write(Document &doc) {
	size_t cntBegin = cntOut.tellp();
	docOut.write((char*)&cntBegin, sizeof(cntBegin));
	
	size_t cntSize = 0;
	for (auto it = doc.fields.begin(); it != doc.fields.end(); it ++) {
		Field& field = it->second;
		const string &fieldName = field.getFieldName();
		addFieldName(fieldName);
		field.writeTo(mmIndex, fieldNameMap, currentDocID);

		size_t fieldID = fieldNameMap.getFieldID(fieldName);

		if ( dynamic_cast<StringField*>(&field) ) {
			cntOut.write((char*)&fieldID, sizeof(fieldID));
			string fieldValue = field.get();
			cntOut.write(fieldValue.c_str(), fieldValue.length() + 1);
			cntSize ++;
		}
	}
	docOut.write((char*)&cntSize, sizeof(cntSize));
	currentDocID ++;
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

	mmIndex.writeTo(idxOut, fldOut, trmOut, pstOut, fieldNameMap.size());
	fieldNameMap.save(fldOut);

	idxOut.close();
	fldOut.close();
	trmOut.close();
	pstOut.close();

	docOut.close();
	cntOut.close();
	merge();
	string cmd = "rm -f ";
	cmd += dirPath;
	cmd += "/__*";
	system(cmd.c_str());
}


