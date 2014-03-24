#ifndef _VB_CODEC_H_
#define _VB_CODEC_H_

#include <Codec.h>


class VBCodec : public Codec {
public:
	virtual void encode(ostream &out, size_t val) const;
	virtual size_t decode(istream &in) const;
	virtual ~VBCodec() {}
};

#endif
