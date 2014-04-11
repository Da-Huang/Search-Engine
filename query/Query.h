#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <ScoreDoc.h>
#include <Codec.h>
#include <IndexSearcher.h>

using namespace std;

class IndexSearcher;

class Query {
protected:
	double boost;

	Query() : boost(1) {}
public:
	virtual inline void setBoost(double boost) { this->boost = boost; }
	virtual inline double getBoost() const { return boost; }
	virtual vector<ScoreDoc> search(IndexSearcher &is) const = 0;
	virtual string toString() const = 0;
	virtual map<string, double> fetchScoreTerms(
			IndexSearcher &is) const = 0;
	virtual ~Query() {}
};


#endif
