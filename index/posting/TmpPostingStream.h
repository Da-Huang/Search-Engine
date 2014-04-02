#ifndef _TMP_POSTING_STREAM_H_
#define _TMP_POSTING_STREAM_H_

#include <cstdio>
#include <PostingStream.h>


class TmpPostingStream : public PostingStream {
protected:
	FILE *fp;
public:
	TmpPostingStream() : fp(tmpfile()) {}
	virtual void write(const Posting &posting);
	virtual Posting next();
	virtual Posting peek();
	virtual tuple<size_t, size_t> nextDocIDTF();
	virtual size_t nextDocID();
	virtual size_t peekDocID();
	virtual ~TmpPostingStream();
};

#endif
