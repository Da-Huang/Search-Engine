#include <fstream>
#include <IndexMerger.h>


IndexMerger::IndexMerger(const string &path) {
	string fldPath = path;
	fldPath += "/_.fld";
	ifstream fldIn(fldPath);

	fieldNameMap = new FieldNameMap;
	fieldNameMap->load(fldIn);
	fldIn.close();

//	size_t recordSize = (fieldNameMap->size() * 2 + 1) * sizeof(size_t)
}
