#ifndef _POSTING_STREAM_H_
#define _POSTING_STREAM_H_

#include <iostream>
#include <Posting.h>
#include <SkipEntry.h>

using namespace std;


class PostingStream {
protected:
	istream &in;
	ostream &out;
	size_t begin;
	size_t end;
	size_t current;
	
	vector<SkipEntry> skips;

public:
	PostingStream(ostream &out=cout, size_t begin=0, size_t end=0)
		: in(cin), out(out), begin(begin), end(end), current(begin) {}
	PostingStream(istream &in, size_t begin, size_t end);
	void writeMerge(vector<PostingStream*> &psv);
	virtual void write(const Posting &posting);
	virtual void writeSkips();
	virtual inline size_t getBegin() const { return begin; }
	virtual inline size_t getEnd() const { return end; }
	virtual Posting next();
	virtual Posting peek();
	virtual size_t nextDocID();
	virtual size_t peekDocID();
	virtual inline bool hasNext() const { return current < end; }
	virtual string toString();
	virtual ~PostingStream() {}
	virtual string info();
};

#endif

