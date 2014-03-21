#include <fstream>
#include <IndexMerger.h>


IndexMerger::IndexMerger(const string &path) {
	string fldPath = path;
	fldPath += "/_.fld";
	ifstream fldIn(fldPath);

	fieldNameMap = new FieldNameMap;
	fieldNameMap->load(fldIn);
	fldIn.close();

	string trmPath = path;
	trmPath += "/_.trm";
	string idxPath = path;
	idxPath += "/_.idx";
	string pstPath = path;
	pstPath += "/_.pst";

	trmOut.open(trmPath);
	idxOut.open(idxPath);
	pstOut.open(pstPath);

	string metaPath = path;
	metaPath += "__.meta";
	ifstream metaIn(metaPath);
	metaIn.close();
}

void IndexMerger::merge() {
}

void IndexMerger::close() {
	trmOut.close();
	idxOut.close();
	pstOut.close();
}

IndexMerger::~IndexMerger() {
	for (size_t i = 0; i < fileIndexes.size(); i ++)
		delete fileIndexes[i];
	delete fieldNameMap;
}


