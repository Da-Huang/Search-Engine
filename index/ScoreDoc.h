#ifndef _SCORE_DOC_H_
#define _SCORE_DOC_H_

#include <Document.h>

class ScoreDoc {
private:
	size_t docID;
	double score;
public:
	ScoreDoc(size_t docID, double score=0) : docID(docID), score(score) {}
	virtual inline size_t id() const { return docID; }
	virtual ~ScoreDoc() {}
};


#endif
