#include <cstdio>
#include <cassert>
#include <VBCodec.h>


void VBCodec::encode(ostream &out, size_t val) const {
	do {
		char c = val & 0x7F;
		val >>= 7;
		if ( val == 0 ) c |= 0x80;
		out.write(&c, sizeof(char));
	} while ( val );
}

size_t VBCodec::decode(istream &in) const {
	size_t val = 0;
	size_t lshift = 0;
	char c;
	do {
		in.read(&c, sizeof(char));
		val |= (c & 0x7F) << lshift;
		lshift += 7;
	} while ( (c & 0x80) == 0 );
	return val;
}

size_t VBCodec::bytes(size_t val) const {
	size_t res = 0;
	do {
		char c = val & 0x7F;
		val >>= 7;
		if ( val == 0 ) c |= 0x80;
		res ++;
	} while ( val );
	return res;
}

void VBCodec::encode(FILE *fp, size_t val) const {
	do {
		char c = val & 0x7F;
		val >>= 7;
		if ( val == 0 ) c |= 0x80;
		fwrite(&c, sizeof(char), 1, fp);
	} while ( val );
}

size_t VBCodec::decode(FILE *fp) const {
	size_t val = 0;
	size_t lshift = 0;
	char c;
	do {
		size_t status = fread(&c, sizeof(char), 1, fp);
		assert (status == 1);
		val |= (c & 0x7F) << lshift;
		lshift += 7;
	} while ( (c & 0x80) == 0 );
	return val;
}


