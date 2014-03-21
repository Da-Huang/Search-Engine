#include <queue>
#include <fstream>
#include <IndexMerger.h>
#include <GreaterFileIndex.h>


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
//		cout << fileIndex->toString() << endl;
	}
}

void IndexMerger::merge() {
	vector<size_t> index(fileIndexes.size(), 0);
	GreaterFileIndex gfi(fileIndexes, index);
	priority_queue<size_t, vector<size_t>, GreaterFileIndex> pq(gfi);
	for (size_t i = 0; i < index.size(); i ++) pq.push(i);
	
	while ( !pq.empty() ) {
		vector<size_t> indexSet;
		size_t i = pq.top();
		indexSet.push_back(i);
		pq.pop();
		string term = fileIndexes[i]->fetchTerm(index[i]);

		while ( !pq.empty() ) {
			i = pq.top();
			if ( fileIndexes[i]->fetchTerm(index[i]) != term ) break;
			indexSet.push_back(i);
			pq.pop();
		}

		for (size_t j = 1; j <= fieldNameMap->size(); j ++) {
			vector<PostingStream*> psv;
			for (size_t k = 0; k < indexSet.size(); k ++) {
				size_t i = indexSet[k];
				PostingStream *ps = 
					fileIndexes[i]->fetchPostingStream(j, i);
				if ( ps ) psv.push_back(ps);
			}
			PostingStream ps(pstOut, pstOut.tellp(), pstOut.tellp());
			ps.writeMerge(psv);

			size_t pstListBegin = ps.getBegin();
			size_t pstListEnd = ps.getEnd();
			idxOut.write((char*)&pstListBegin, sizeof(pstListBegin));
			idxOut.write((char*)&pstListEnd, sizeof(pstListEnd));
		}
		for (size_t k = 0; k < indexSet.size(); k ++) {
			size_t i = indexSet[k];
			if ( index[i] <= fileIndexes[i]->TERM_NUM ) pq.push(i);
		}
	}
	
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


