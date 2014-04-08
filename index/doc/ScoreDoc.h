#ifndef _SCORE_DOC_H_
#define _SCORE_DOC_H_

#include <string>

using namespace std;


class ScoreDoc {
private:
	size_t docID;
	double docScore;
public:
	ScoreDoc(size_t docID, double score=0) 
		: docID(docID), docScore(score) {}
	virtual inline size_t id() const { return docID; }
	virtual inline double score() const { return docScore; }
	virtual inline void setScore(double score) { docScore = score; }
	virtual inline void operator *= (double boost) { docScore *= boost; }
	virtual inline void operator += (double score) { docScore += score; }
	virtual inline string toString() const {
		string res = "<";
		res += to_string(docID);
		res += ",";
		res += to_string(docScore);
		res += ">";
		return res;
	}
	virtual inline bool operator < (const ScoreDoc &doc) const {
		return docScore > doc.docScore;
	}
	virtual ~ScoreDoc() {}
};


#endif
