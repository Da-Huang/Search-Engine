#ifndef _VB_CODEC_H_
#define _VB_CODEC_H_

#include <Codec.h>


class VBCodec : public Codec {
public:
	VBCodec(bool delta) : Codec(delta) {}
	virtual void encode(ostream &out, size_t val) const;
	virtual size_t bytes(size_t val) const;
	virtual size_t decode(istream &in) const;
	virtual void encode(FILE *fp, size_t val) const;
	virtual size_t decode(FILE *fp) const;

	virtual ~VBCodec() {}
};

#endif
