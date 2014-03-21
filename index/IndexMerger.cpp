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
	metaPath += "/__.meta";
	ifstream metaIn(metaPath);
	size_t segNum;
	metaIn.read((char*)&segNum, sizeof(segNum));
	metaIn.close();

//	cout << segNum << endl;
	for (size_t i = 1; i <= segNum; i ++) {
		string prefix = path;
		prefix += "/__";
		prefix += to_string(i);

		string fldPath = prefix;
		fldPath += ".fld";

		ifstream fldIn(fldPath);
		size_t fieldNum;
		fldIn.read((char*)&fieldNum, sizeof(fieldNum));
		fldIn.close();

//		cout << prefix << endl;
		FileIndex *fileIndex = new FileIndex(prefix, fieldNum);
		fileIndexes.push_back(fileIndex);
		cout << fileIndex->toString() << endl;
	}
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


