#ifndef _POSTING_STREAM_H_
#define _POSTING_STREAM_H_

#include <iostream>
#include <tuple>
#include <Posting.h>
#include <ScoreDoc.h>
#include <SkipEntry.h>

using namespace std;

class IndexSearcher;

class PostingStream {
protected:
	istream &in;
	ostream &out;
	size_t begin;
	size_t end;
	size_t current;
	
	vector<SkipEntry> skips;

	size_t baseDocID;
	size_t df;

public:
	PostingStream(ostream &out=cout, size_t begin=0, size_t end=0)
		: in(cin), out(out), begin(begin), end(end), current(begin), 
			baseDocID(0), df(0) {}

	PostingStream(istream &in, size_t begin, size_t df, size_t end);
	virtual void rewind();

	virtual void writeMerge(vector<PostingStream*> &psv, 
			IndexSearcher *is=NULL, size_t fieldID=0);
	virtual void write(const Posting &posting, double score=0);
	virtual void writeSkips();
	virtual inline size_t getBegin() const { return begin; }
	virtual inline size_t getDF() const { return df; }
	virtual inline size_t getEnd() const { return end; }
	virtual Posting next();
	virtual Posting peek();
	virtual inline size_t size() const { return end - begin; }
	virtual tuple<size_t, size_t> nextDocIDTF();
	virtual size_t nextDocID();
	virtual size_t peekDocID();
	virtual inline bool hasNext() const { return current < end; }
	virtual string toString();
	virtual ~PostingStream();
	virtual string info();

	virtual double peekScore(IndexSearcher &is, size_t fieldID);
	virtual vector<ScoreDoc> getScoreDocs(
			IndexSearcher &is, size_t fieldID);
};

#endif
