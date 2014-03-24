#ifndef _CODEC_H_
#define _CODEC_H_

#include <iostream>

using namespace std;


class Codec {
public:
	virtual void encode(ostream &out, size_t val) const;
	virtual size_t decode(istream &in) const;
	virtual void encode(FILE *fp, size_t val) const;
	virtual size_t decode(FILE *fp) const;

	virtual ~Codec() {}
};

#endif
