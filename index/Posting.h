#ifndef _POSTING_H_
#define _POSTING_H_

#include <iostream>

class Posting {
private:
	size_t docID;
public:
	Posting(size_t docID) : docID(docID) {}
	virtual ~Posting() {}
};

#endif
