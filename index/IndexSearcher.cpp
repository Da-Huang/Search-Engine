#include <fstream>
#include <util.h>
#include <Query.h>
#include <algorithm>
#include <IndexSearcher.h>


IndexSearcher::IndexSearcher(const string &dirPath) {
	string prefix = util::join("", {dirPath, "/_"});
	ifstream fldIn(util::join("", {prefix, ".fld"}));

	fieldNameMap = new FieldNameMap;
	fieldNameMap->load(fldIn);
	fldIn.close();
//	cerr << fieldNameMap->toString() << endl;

	fileIndex = new FileIndex(prefix, fieldNameMap->size());
	docDB = new DocDB(prefix, *fieldNameMap, fieldNameMap->size());
}

vector<ScoreDoc> IndexSearcher::search(const Query &query) {
	vector<ScoreDoc> res = query.search(*this);
//	sort(res.begin(), res.end());
	return res;
}

Document IndexSearcher::doc(const ScoreDoc &scoreDoc) {
	/*
	cerr << docDB->getDocFieldDL(scoreDoc.id(), 1) << "\t"
		<< docDB->getDocFieldDL(scoreDoc.id(), 2) << "\t" 
		<< docDB->getDocFieldDL(scoreDoc.id(), 3) << endl;
		*/
	/*
	cerr << fieldNameMap->getAvgdl(1) << "\t"
		<< fieldNameMap->getAvgdl(2) << "\t"
		<< fieldNameMap->getAvgdl(3) << endl;
		*/
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


