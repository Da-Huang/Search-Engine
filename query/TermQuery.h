#ifndef _TERM_QUERY_H_
#define _TERM_QUERY_H_

#include <Query.h>


class TermQuery : public Query {
private:
	string field;
	string term;
public:
	TermQuery(const string &field, const string &term) 
		: field(field), term(term) {}
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	virtual ~TermQuery() {}

	friend class FileIndex;
};



#endif
