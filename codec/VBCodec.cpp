#include <cstdio>
#include <cassert>
#include <VBCodec.h>


void VBCodec::encode(ostream &out, size_t val) const {
	while ( val ) {
		char c = val & 0x7F;
		val >>= 7;
		if ( val == 0 ) c |= 0x80;
		out.write(&c, sizeof(char));
	}
}

size_t VBCodec::decode(istream &in) const {
	size_t val = 0;
	size_t lshift = 0;
	char c;
	do {
		in.read(&c, sizeof(char));
		val |= (c & 0x7F) << lshift;
		lshift += 7;
	} while ( c & 0x80 );
	return val;
}

void VBCodec::encode(FILE *fp, size_t val) const {
	while ( val ) {
		char c = val & 0x7F;
		val >>= 7;
		if ( val == 0 ) c |= 0x80;
		fwrite(&c, sizeof(char), 1, fp);
	}
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
	} while ( c & 0x80 );
	return val;
}


