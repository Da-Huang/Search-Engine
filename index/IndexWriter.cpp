#include <util.h>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <StringField.h>
#include <IndexWriter.h>
#include <IndexMerger.h>


void IndexWriter::setMaxMBSize(size_t maxMBSize) {
	MAX_SIZE = util::MBtoB(maxMBSize);
}

void IndexWriter::addFieldName(const string &fieldName) {
	fieldNameMap.addFieldName(fieldName);
}

IndexWriter::IndexWriter(const string &dirPath) 
	: dirPath(dirPath), currentDocID(1), currentSegID(1), 
		MAX_SIZE(util::MBtoB(1024)) {
//		MAX_SIZE(util::MBtoB(1024)) {

	string cmd = "mkdir -p ";
	cmd += dirPath;
	int status = system(cmd.c_str());
	assert (status == 0);

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

//	cout << mmIndex.size() << "," << MAX_SIZE << endl;
	if ( mmIndex.size() > MAX_SIZE ) saveSegment();
}

void IndexWriter::saveSegment() {
	if ( mmIndex.size() == 0 ) return;
//	cout << mmIndex.toString() << endl;

	string idxPath = dirPath;
	idxPath += "/__";
	idxPath += to_string(currentSegID);
	idxPath += ".idx";
	string fldPath = dirPath;
	fldPath += "/__";
	fldPath += to_string(currentSegID);
	fldPath += ".fld";
	string trmPath = dirPath;
	trmPath += "/__";
	trmPath += to_string(currentSegID);
	trmPath += ".trm";
	string pstPath = dirPath;
	pstPath += "/__";
	pstPath += to_string(currentSegID);
	pstPath += ".pst";

	ofstream idxOut(idxPath);
	ofstream fldOut(fldPath);
	ofstream trmOut(trmPath);
	ofstream pstOut(pstPath);

	mmIndex.writeTo(idxOut, fldOut, trmOut, pstOut, fieldNameMap.size());
	fieldNameMap.save(fldOut);
	mmIndex.reset();

	idxOut.close();
	fldOut.close();
	trmOut.close();
	pstOut.close();
	
	currentSegID ++;
}

void IndexWriter::close() {
	saveSegment();
	docOut.close();
	cntOut.close();

	string fldPath = dirPath;
	fldPath += "/_.fld";
	ofstream fldOut(fldPath);

	size_t fieldNum = fieldNameMap.size();
	fldOut.write((char*)&fieldNum, sizeof(fieldNum));
	fieldNameMap.save(fldOut);
	fldOut.close();

	string metaPath = dirPath;
	metaPath += "/__.meta";
	ofstream metaOut(metaPath);
	size_t segNum = currentSegID - 1;
	metaOut.write((char*)&segNum, sizeof(segNum));
	metaOut.close();

	IndexMerger indexMerger(dirPath);
	indexMerger.merge();
	indexMerger.close();

	string cmd = "rm -f ";
	cmd += dirPath;
	cmd += "/__*";
	size_t status = system(cmd.c_str());
	assert (status == 0);
}

string IndexWriter::toString() const {
	return mmIndex.toString();
}


