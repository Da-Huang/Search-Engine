#include <util.h>
#include <Posting.h>


Posting::Posting(istream &in, size_t baseDocID) {
	readFrom(in, baseDocID);
}

Posting::Posting(FILE *fp, size_t baseDocID) {
	readFrom(fp, baseDocID);
}

size_t Posting::merge(const Posting &posting) {
	cerr << "Merge not supported in Posting." << endl;
	throw string("Unsupported Method.");
}

/** delta is for delta pos **/
void Posting::writeTo(ostream &out, size_t baseDocID) const {

	util::codec.encode(out, 
			util::codec.isDelta() ? docID - baseDocID : docID);
	util::codec.encode(out, posList.size());
	size_t basePos = 0;
	for (auto posIt = posList.begin(); posIt != posList.end(); posIt ++) {
		util::codec.encode(out, 
				util::codec.isDelta() ? *posIt - basePos : *posIt);
		basePos = *posIt;
	}
}

void Posting::readFrom(istream &in, size_t baseDocID) {

	docID = util::codec.decode(in) + 
			(util::codec.isDelta() ? baseDocID : 0);
	size_t posListSize = util::codec.decode(in);

	size_t basePos = 0;
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos = util::codec.decode(in) + 
				(util::codec.isDelta() ? basePos : 0);
		basePos = pos;
		addPos(pos);
	}
}

void Posting::readFrom(FILE *fp, size_t baseDocID) {

	docID = util::codec.decode(fp) + 
			(util::codec.isDelta() ? baseDocID : 0);
	size_t posListSize = util::codec.decode(fp);

	size_t basePos = 0;
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos = util::codec.decode(fp) + 
				(util::codec.isDelta() ? basePos : 0);
		basePos = pos;
		addPos(pos);
	}
}

/** delta is for delta pos **/
void Posting::writeTo(FILE *fp, size_t baseDocID) const {

	util::codec.encode(fp, 
			util::codec.isDelta() ? docID - baseDocID : docID);
	util::codec.encode(fp, posList.size());
	size_t basePos = 0;
	for (auto posIt = posList.begin(); 
			posIt != posList.end(); posIt ++) {
		util::codec.encode(fp, 
				util::codec.isDelta() ? *posIt - basePos : *posIt);
		basePos = *posIt;
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


