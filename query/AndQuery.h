#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_


#include <Query.h>


class AndQuery : public Query {
private:
	vector<Query> queries;
public:
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual ~AndQuery() {}
};


#endif
