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
		MAX_SIZE(util::MBtoB(128)) {
//		MAX_SIZE(util::MBtoB(1024)) {

	int status = system(util::join("", {"mkdir -p ", dirPath}).c_str());
	assert (status == 0);

	docOut.open(util::join("", {dirPath, "/_.doc"}));
	cntOut.open(util::join("", {dirPath, "/_.cnt"}));
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

	ofstream idxOut(util::join("", 
				{dirPath, "/__", to_string(currentSegID), ".idx"}));
	ofstream fldOut(util::join("",
				{dirPath, "/__", to_string(currentSegID), ".fld"}));
	ofstream trmOut(util::join("",
				{dirPath, "/__", to_string(currentSegID), ".trm"}));
	ofstream pstOut(util::join("",
				{dirPath, "/__", to_string(currentSegID), ".pst"}));

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

	ofstream fldOut(util::join("", {dirPath, "/_.fld"}));

	size_t fieldNum = fieldNameMap.size();
	fldOut.write((char*)&fieldNum, sizeof(fieldNum));
	fieldNameMap.save(fldOut);
	fldOut.close();

	ofstream metaOut(util::join("", {dirPath, "/__.meta"}));
	size_t segNum = currentSegID - 1;
	metaOut.write((char*)&segNum, sizeof(segNum));
	metaOut.close();

	IndexMerger indexMerger(dirPath);
	indexMerger.merge();
	indexMerger.close();

	size_t status = system(util::join("", 
				{"rm -f ", dirPath, "/__*"}).c_str());
	assert (status == 0);
}

string IndexWriter::toString() const {
	return mmIndex.toString();
}


