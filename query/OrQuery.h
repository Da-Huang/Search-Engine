#ifndef _OR_QUERY_H_
#define _OR_QUERY_H_


#include <Query.h>


class OrQuery : public Query {
private:
	vector<const Query*> queries;
public:
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	virtual ~OrQuery();
};


#endif
