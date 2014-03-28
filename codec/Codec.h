#ifndef _CODEC_H_
#define _CODEC_H_

#include <iostream>

using namespace std;


class Codec {
private:
	bool delta;
public:
	Codec(bool delta=false) : delta(delta) {}
	virtual inline bool isDelta() const { return delta; }
	virtual void encode(ostream &out, size_t val) const;
	virtual size_t bytes(size_t val) const;
	virtual size_t decode(istream &in) const;
	virtual void encode(FILE *fp, size_t val) const;
	virtual size_t decode(FILE *fp) const;

	virtual ~Codec() {}
};

#endif
