#ifndef _TERM_QUERY_H_
#define _TERM_QUERY_H_

#include <Query.h>


class TermQuery : public Query {
private:
	string term;
public:
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
};



#endif
