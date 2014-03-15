#ifndef _GREATER_POSTING_STREAM_H_
#define _GREATER_POSTING_STREAM_H_

#include <PostingStream.h>


class GreaterPostingStream {
public:
	bool operator () (PostingStream *ps1, PostingStream *ps2) const {
		return ps1->peekDocID() >= ps2->peekDocID();
	}
};


#endif
