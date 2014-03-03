#include <Posting.h>

size_t Posting::merge(const Posting &posting) {
	if ( docID != posting.docID ) return 0;
	return 0;
}

void Posting::writeTo(ostream &out) const {
	out.write((char*)&docID, sizeof(docID));
}

string Posting::toString() const {
	return to_string(docID);
}
