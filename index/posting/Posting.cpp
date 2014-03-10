#include <Posting.h>


size_t Posting::merge(const Posting &posting) {
	if ( docID != posting.docID ) return 0;
	return 0;
}

void Posting::writeTo(ostream &out) const {
	out.write((char*)&docID, sizeof(docID));
	size_t posListSize = posList.size();
	out.write((char*)&posListSize, sizeof(posListSize));
	for (auto posIt = posList.begin(); 
			posIt != posList.end(); posIt ++) {
		out.write((char*)&*posIt, sizeof(*posIt));
	}
}

string Posting::toString() const {
	string res = "<";
	res += to_string(docID);
	res += ":";
	for (auto posIt = posList.begin(); 
			posIt != posList.end(); posIt ++) {
		res += to_string(*posIt);
		res += ",";
	}
	if ( res.back() == ',' ) res.erase(res.length() - 1);
	res += ">";
	return res;
}

size_t Posting::size() const {
	return sizeof(docID) + posList.size() * sizeof(size_t);
}


