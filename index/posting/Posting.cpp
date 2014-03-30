#include <util.h>
#include <Posting.h>


Posting::Posting(istream &in, size_t baseDocID) : plBytes(0), basePos(0) {
	readFrom(in, baseDocID);
}

Posting::Posting(FILE *fp, size_t baseDocID) : plBytes(0), basePos(0) {
	readFrom(fp, baseDocID);
}

Posting::Posting(size_t docID, size_t pos) 
	: docID(docID), plBytes(0), basePos(0) {
	addPos(pos);
}

void Posting::addPos(size_t pos) {
	posList.push_back(pos); 
	plBytes += util::codec.bytes(
			util::codec.isDelta() ? pos - basePos : pos);
	basePos = pos;
}

size_t Posting::merge(const Posting &posting) {
	throw string("Method 'merge' is not supported in Posting.");
}

/** delta is for delta pos **/
void Posting::writeTo(ostream &out, size_t baseDocID) const {

	util::codec.encode(out, 
			util::codec.isDelta() ? docID - baseDocID : docID);
	util::codec.encode(out, posList.size());
	util::codec.encode(out, plBytes);

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
	size_t tf = util::codec.decode(in);
	plBytes = util::codec.decode(in);

	size_t basePos = 0;
	for (size_t i = 0; i < tf; i ++) {
		size_t pos = util::codec.decode(in) + 
				(util::codec.isDelta() ? basePos : 0);
		basePos = pos;
		addPos(pos);
	}
}

void Posting::readFrom(FILE *fp, size_t baseDocID) {

	docID = util::codec.decode(fp) + 
			(util::codec.isDelta() ? baseDocID : 0);
	size_t tf = util::codec.decode(fp);
	plBytes = util::codec.decode(fp);
//	cout << "plbs:" << plBytes << endl;

	size_t basePos = 0;
	for (size_t i = 0; i < tf; i ++) {
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
	util::codec.encode(fp, plBytes);

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
	for (auto posIt = posList.begin(); posIt != posList.end(); posIt ++) {
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


