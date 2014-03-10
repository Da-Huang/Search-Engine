#include <Posting.h>


size_t Posting::merge(const Posting &posting) {
	if ( docID != posting.docID ) return 0;
	return 0;
}

void Posting::writeTo(ostream &out) const {
	out.write((char*)&docID, sizeof(docID));
	size_t posListSize = posList.size();
	out.write((char*)&posListSize, sizeof(posListSize));
	for (auto posListIt = posList.begin(); 
			posListIt != posList.end(); posListIt ++) {
		out.write((char*)&*posListIt, sizeof(*posListIt));
	}
}

string Posting::toString() const {
	return to_string(docID);
}

size_t Posting::size() const {
	return sizeof(docID) + posList.size() * sizeof(size_t);
}


