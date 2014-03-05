#ifndef _NOT_QUERY_H_
#define _NOT_QUERY_H_


#include <Query.h>


class NotQuery : public Query {
private:
	const Query &query;
public:
	NotQuery(const Query &query) : query(query) {}
	NotQuery(const NotQuery &query) : query(query) {}
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	virtual ~NotQuery();
};


#endif
