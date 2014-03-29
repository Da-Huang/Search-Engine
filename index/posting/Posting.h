#ifndef _POSTING_H_
#define _POSTING_H_

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <Codec.h>

using namespace std;

class Posting {
private:
	size_t docID;
	vector<size_t> posList;	
	size_t plBytes;
	size_t basePos;

public:
	Posting(istream &in, size_t baseDocID=0);
	Posting(FILE *fp, size_t baseDocID=0);
	Posting(size_t docID) : docID(docID), plBytes(0), basePos(0) {}
	Posting(size_t docID, size_t pos);

	virtual inline size_t getDocID() const { return docID; }
	virtual void addPos(size_t pos);

	virtual void writeTo(ostream &out, size_t baseDocID=0) const;
	virtual void writeTo(FILE *fp, size_t baseDocID=0) const;

	virtual void readFrom(istream &in, size_t baseDocID=0);
	virtual void readFrom(FILE *fp, size_t baseDocID=0);

	virtual size_t merge(const Posting &posting);
	virtual size_t size() const;
	virtual string toString() const;
	virtual ~Posting() {}

	friend class MMIndex;
	friend class PostingStream;
	friend class PhraseQuery;
	friend class GreaterPos;
	friend class FuzzyQuery;
};

#endif
