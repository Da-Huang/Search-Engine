#include <queue>
#include <fstream>
#include <cassert>
#include <util.h>
#include <IndexMerger.h>
#include <GreaterFileIndex.h>


IndexMerger::IndexMerger(const string &path) {
	string fldPath = path;
	fldPath += "/_.fld";
	ifstream fldIn(fldPath);

	fieldNameMap.load(fldIn);
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
	// TODO: There're fatal problem if segNum > 200
	assert (segNum <= 200);
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
	size_t count = 0;

	vector<size_t> termIndex(fileIndexes.size(), 1);
	GreaterFileIndex gfi(fileIndexes, termIndex);
	priority_queue<size_t, vector<size_t>, GreaterFileIndex> pq(gfi);
	for (size_t i = 0; i < termIndex.size(); i ++) pq.push(i);

	while ( !pq.empty() ) {
		vector<size_t> indexSet;
		size_t i = pq.top();
		indexSet.push_back(i);
		pq.pop();
		string term = fileIndexes[i]->fetchTerm(termIndex[i]);
		size_t termBegin = trmOut.tellp();
		idxOut.write((char*)&termBegin, sizeof(termBegin));
		trmOut.write(term.c_str(), term.length() + 1);
//		cerr << term << endl;

		while ( !pq.empty() ) {
			i = pq.top();
			if ( fileIndexes[i]->fetchTerm(termIndex[i]) != term ) break;
			indexSet.push_back(i);
			pq.pop();
		}

		for (size_t j = 1; j <= fieldNameMap.size(); j ++) {
			vector<PostingStream*> psv;
			for (size_t k = 0; k < indexSet.size(); k ++) {
				size_t i = indexSet[k];
				PostingStream *ps = 
					fileIndexes[i]->fetchPostingStream(j, termIndex[i]);
				if ( ps ) psv.push_back(ps);
			}
			PostingStream ps(pstOut, pstOut.tellp(), pstOut.tellp());
//			cerr << "emrge" << psv.size() <<endl;
//			cerr << psv[0]->toString() << endl;
			if ( psv.size() > 0 ) {
				ps.writeMerge(psv);
				ps.writeSkips();
			}

			size_t pstListBegin = ps.getBegin();
			size_t pstListEnd = ps.getEnd();
//			cout << "merge:" <<  pstListBegin << " " << pstListEnd << endl;
			idxOut.write((char*)&pstListBegin, sizeof(pstListBegin));
			idxOut.write((char*)&pstListEnd, sizeof(pstListEnd));
		}
		for (size_t k = 0; k < indexSet.size(); k ++) {
			size_t i = indexSet[k];
			termIndex[i] ++;
			if ( termIndex[i] <= fileIndexes[i]->TERM_NUM ) pq.push(i);
		}
		
		if ( ++ count % 10000 == 0 ) cerr << ".";
	}
	cerr << endl;
}

void IndexMerger::close() {
	trmOut.close();
	idxOut.close();
	pstOut.close();
}

IndexMerger::~IndexMerger() {
	for (size_t i = 0; i < fileIndexes.size(); i ++)
		delete fileIndexes[i];
}


