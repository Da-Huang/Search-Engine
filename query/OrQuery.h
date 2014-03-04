#ifndef _OR_QUERY_H_
#define _OR_QUERY_H_


#include <Query.h>


class OrQuery {
private:
	vector<Query> queries;
public:
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual ~OrQuery() {}
};


#endif
