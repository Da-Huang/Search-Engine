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
public:
	Posting(istream &in, const Codec &codec=Codec(), size_t baseDocID=0);
	Posting(FILE *fp, const Codec &codec=Codec(), size_t baseDocID=0);
	Posting(size_t docID) : docID(docID) {}
	Posting(size_t docID, size_t pos) : docID(docID), posList(1, pos) {}

	virtual void addPos(size_t pos) { posList.push_back(pos); }
	virtual inline size_t getDocID() const { return docID; }

	virtual void writeTo(ostream &out, const Codec &codec=Codec(), 
			size_t baseDocID=0) const;
	virtual void writeTo(FILE *fp, const Codec &codec=Codec(), 
			size_t baseDocID=0) const;

	virtual void readFrom(istream &in, const Codec &codec=Codec(), 
			size_t baseDocID=0);
	virtual void readFrom(FILE *fp, const Codec &codec=Codec(), 
			size_t baseDocID=0);

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
