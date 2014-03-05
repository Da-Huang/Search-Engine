#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_


#include <Query.h>


class AndQuery : public Query {
private:
	vector<const Query*> queries;
	static vector<ScoreDoc> merge(
		const vector<ScoreDoc> &docs1, const vector<ScoreDoc> &docs2);
public:
	AndQuery() {}
	AndQuery(const Query &q1, const Query &q2);
	virtual void add(const Query &query) { queries.push_back(&query); };
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	virtual ~AndQuery();
};


#endif
