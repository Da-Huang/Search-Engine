#include <Posting.h>


Posting::Posting(istream &in, const Codec &codec, size_t baseDocID) {
	readFrom(in, codec, baseDocID);
}

Posting::Posting(FILE *fp, const Codec &codec, size_t baseDocID) {
	readFrom(fp, codec, baseDocID);
}

size_t Posting::merge(const Posting &posting) {
	cerr << "Merge not supported in Posting." << endl;
	throw string("Unsupported Method.");
//	if ( docID != posting.docID ) return 0;
//	return posting.size();
}

/** delta is for delta pos **/
void Posting::writeTo(ostream &out, const Codec &codec, 
		size_t baseDocID) const {

	codec.encode(out, codec.isDelta() ? docID - baseDocID : docID);
	codec.encode(out, posList.size());
	size_t basePos = 0;
	for (auto posIt = posList.begin(); posIt != posList.end(); posIt ++) {
		codec.encode(out, codec.isDelta() ? *posIt - basePos : *posIt);
		basePos = *posIt;
	}
	/*
	out.write((char*)&docID, sizeof(docID));
	size_t posListSize = posList.size();
	out.write((char*)&posListSize, sizeof(posListSize));
	for (auto posIt = posList.begin(); 
			posIt != posList.end(); posIt ++) {
		out.write((char*)&*posIt, sizeof(*posIt));
	}
	*/
}

void Posting::readFrom(istream &in, const Codec &codec, size_t baseDocID) {

	docID = codec.decode(in) + (codec.isDelta() ? baseDocID : 0);
	size_t posListSize = codec.decode(in);

	size_t basePos = 0;
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos = codec.decode(in) + (codec.isDelta() ? basePos : 0);
		basePos = pos;
		addPos(pos);
	}
}

void Posting::readFrom(FILE *fp, const Codec &codec, size_t baseDocID) {

	docID = codec.decode(fp) + (codec.isDelta() ? baseDocID : 0);
	size_t posListSize = codec.decode(fp);

	size_t basePos = 0;
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos = codec.decode(fp) + (codec.isDelta() ? basePos : 0);
		basePos = pos;
		addPos(pos);
	}
}

/** delta is for delta pos **/
void Posting::writeTo(FILE *fp, const Codec &codec,
		size_t baseDocID) const {

	codec.encode(fp, codec.isDelta() ? docID - baseDocID : docID);
	codec.encode(fp, posList.size());
	size_t basePos = 0;
	for (auto posIt = posList.begin(); 
			posIt != posList.end(); posIt ++) {
		codec.encode(fp, codec.isDelta() ? *posIt - basePos : *posIt);
		basePos = *posIt;
	}
	/*
	fwrite(&docID, sizeof(docID), 1, fp);
	size_t posListSize = posList.size();
	fwrite(&posListSize, sizeof(posListSize), 1, fp);
	for (auto posIt = posList.begin(); 
			posIt != posList.end(); posIt ++) {
		fwrite(&*posIt, sizeof(*posIt), 1, fp);
	}
	*/
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


