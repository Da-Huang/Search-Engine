#include <Posting.h>

void Posting::merge(const Posting &posting) {
	if ( docID != posting.docID ) return;
	return;
}

void Posting::writeTo(ostream &out) const {
	out.write((char*)&docID, sizeof(docID));
}


