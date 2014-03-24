#include <VBCodec.h>


void VBCodec::encode(ostream &out, size_t val) const {
	Codec::encode(out, val);
}


size_t VBCodec::decode(istream &in) const {
	return Codec::decode(in);
}


