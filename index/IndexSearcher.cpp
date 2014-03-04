#include <fstream>
#include <IndexSearcher.h>
#include <Query.h>


IndexSearcher::IndexSearcher(const string &prefix) {
	string fldPath = prefix;
	fldPath += ".fld";
	ifstream fldIn(fldPath);

	FieldNameMap fieldNameMap;
	fieldNameMap.load(fldIn);
	fldIn.close();
	size_t recordSize = (fieldNameMap.size() * 2 + 1) * sizeof(size_t);

	fileIndex = new FileIndex(prefix, recordSize);
	docDB = new DocDB(prefix, fieldNameMap);
}

TopDoc IndexSearcher::search(const Query &query) {
	return TopDoc(0, vector<ScoreDoc>());
}

Document IndexSearcher::doc(const ScoreDoc &scoreDoc) {
	return docDB->fetchDocument(scoreDoc.id());
}

IndexSearcher::~IndexSearcher() {
	delete fileIndex;
	delete docDB;
}

