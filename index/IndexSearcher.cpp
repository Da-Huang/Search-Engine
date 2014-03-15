#include <fstream>
#include <IndexSearcher.h>
#include <Query.h>


IndexSearcher::IndexSearcher(const string &prefix) {
	string fldPath = prefix;
	fldPath += ".fld";
	ifstream fldIn(fldPath);

	fieldNameMap = new FieldNameMap;
	fieldNameMap->load(fldIn);
	fldIn.close();
	size_t recordSize = (fieldNameMap->size() * 2 + 1) * sizeof(size_t);

	fileIndex = new FileIndex(prefix, recordSize);
	docDB = new DocDB(prefix, *fieldNameMap);
}

vector<ScoreDoc> IndexSearcher::search(const Query &query) {
	return query.search(*this);
}

Document IndexSearcher::doc(const ScoreDoc &scoreDoc) {
	return docDB->fetchDocument(scoreDoc.id());
}

string IndexSearcher::toString() {
	string res = fileIndex->toString();
	res += "\n";
	res += docDB->toString();
	return res;
}

IndexSearcher::~IndexSearcher() {
	delete fileIndex;
	delete docDB;
	delete fieldNameMap;
}


