#include <SkipEntry.h>


void SkipEntry::read(istream &in) const {
	in.read((char*)&docID, sizeof(docID));
	in.read((char*)&skipTo, sizeof(skipTo));
}

void SkipEntry::writeTo(ostream &out) const {
	out.write((char*)&docID, sizeof(docID));
	out.write((char*)&skipTo, sizeof(skipTo));
}

string SkipEntry::toString() const {
	string res = "<";
	res += to_string(docID);
	res += "->";
	res += to_string(docID);
	res += ">";
	return res;
}

