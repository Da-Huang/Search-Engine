#ifndef _SCORE_DOC_H_
#define _SCORE_DOC_H_

#include <cassert>
#include <Document.h>

class ScoreDoc {
private:
	size_t docID;
	double docScore;
public:
	ScoreDoc(size_t docID, double score=0) 
		: docID(docID), docScore(score) {}
	virtual inline size_t id() const { return docID; }
	virtual inline double score() const { return docScore; }
	virtual inline void operator *= (double boost) { docScore *= boost; }
	virtual ~ScoreDoc() {}
};


#endif
