#include <util.h>
#include <DocDBSorter.h>
#include <FieldNameMap.h>


DocDBSorter::DocDBSorter(const string &dirPath, 
		FieldNameMap &fieldNameMap) : fieldNameMap(fieldNameMap) {

	docDB = new DocDB(util::join("", {dirPath, "/_"}), fieldNameMap);
	docOut.open(util::join("", {dirPath, "/__.doc"}));
}

void DocDBSorter::sort() {
	static const size_t zeroDL = 0;
	fieldNameMap.initSumdls();

	for (size_t docID = 1; docID <= docDB->DOC_NUM; docID ++) {
		double staticScore = docDB->getDocStaticScore(docID);
		docOut.write((char*)&staticScore, sizeof(staticScore));
		size_t cntBegin, cntSize;
		tie(cntBegin, cntSize) = docDB->getDocCntInfo(docID);
		docOut.write((char*)&cntBegin, sizeof(cntBegin));
		docOut.write((char*)&cntSize, sizeof(cntSize));

		docDB->cntIn.seekg(cntBegin);
		size_t lastFieldID = 0;
		for (size_t i = 0; i < cntSize; i ++) {

			size_t fieldID = util::codec.decode(docDB->cntIn);
			size_t dl  = util::codec.decode(docDB->cntIn);
			size_t length = util::codec.decode(docDB->cntIn);
//			cerr << fieldID << " " << dl << " " << length << endl;

			for (size_t j = lastFieldID + 1; j < fieldID; j ++)
				docOut.write((char*)&zeroDL, sizeof(zeroDL));

			docDB->cntIn.seekg(length, ios::cur);
			docOut.write((char*)&dl, sizeof(dl));

			fieldNameMap.addToSumdl(fieldID, dl);
			lastFieldID = fieldID;
		}
		const size_t FIELD_NUM = fieldNameMap.size();
		for (size_t j = lastFieldID + 1; j <= FIELD_NUM; j ++)
			docOut.write((char*)&zeroDL, sizeof(zeroDL));

		if ( docID % 10000 == 0 ) cerr << ".";
	}
	fieldNameMap.genAvgdls(docDB->getDocNum());
	cerr << endl;
}

void DocDBSorter::close() {
	docOut.close();
	delete docDB;
}


