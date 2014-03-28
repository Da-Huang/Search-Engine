#include <cstdio>
#include <cassert>
#include <Codec.h>


void Codec::encode(ostream &out, size_t val) const {
	out.write((char*)&val, sizeof(val));
}

size_t Codec::decode(istream &in) const {
	size_t val;
	in.read((char*)&val, sizeof(val));	
	return val;
}

size_t Codec::bytes(size_t val) const {
	return sizeof(val);
}

void Codec::encode(FILE *fp, size_t val) const {
	fwrite(&val, sizeof(val), 1, fp);
}

size_t Codec::decode(FILE *fp) const {
	size_t val;
	size_t status = fread(&val, sizeof(val), 1, fp);	
	assert (status == 1);
	return val;
}


