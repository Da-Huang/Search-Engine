#ifndef _POSTING_STREAM_H_
#define _POSTING_STREAM_H_

#include <istream>
#include <Posting.h>
#include <SkipEntry.h>

using namespace std;


class PostingStream {
private:
	istream &in;
	size_t begin;
	size_t end;
	size_t current;
	
	vector<SkipEntry> skips;

public:
	PostingStream(istream &in, size_t begin, size_t end);
	virtual Posting next();
	virtual Posting peek();
	virtual size_t nextDocID();
	virtual size_t peekDocID();
	virtual inline bool hasNext() const { return current < end; }
	virtual ~PostingStream() {}
};

#endif

