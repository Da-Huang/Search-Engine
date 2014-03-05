#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <ScoreDoc.h>
#include <IndexSearcher.h>

using namespace std;

class IndexSearcher;

class Query {
public:
	virtual vector<ScoreDoc> search(IndexSearcher &is) const = 0;
	virtual string toString() const = 0;
	virtual ~Query() {}
};


#endif
