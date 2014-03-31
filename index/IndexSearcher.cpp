#include <fstream>
#include <util.h>
#include <IndexSearcher.h>
#include <Query.h>


IndexSearcher::IndexSearcher(const string &dirPath) {
	string prefix = util::join("", {dirPath, "/_"});
	ifstream fldIn(util::join("", {prefix, ".fld"}));

	fieldNameMap = new FieldNameMap;
	fieldNameMap->load(fldIn);
	fldIn.close();
//	size_t recordSize = (fieldNameMap->size() * 2 + 1) * sizeof(size_t);

	fileIndex = new FileIndex(prefix, fieldNameMap->size());
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


