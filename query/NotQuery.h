#ifndef _NOT_QUERY_H_
#define _NOT_QUERY_H_


#include <Query.h>

class NotQuery {
private:
	const Query &query;
public:
	NotQuery(const Query &query) : query(query) {}
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual ~NotQuery() {}
};


#endif
