#include <Codec.h>


void Codec::encode(ostream &out, size_t val) const {
	out.write((char*)&val, sizeof(val));
}

size_t Codec::decode(istream &in) const {
	size_t val;
	in.read((char*)&val, sizeof(val));	
	return val;
}


