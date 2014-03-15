#ifndef _FUZZY_QUERY_H_
#define _FUZZY_QUERY_H_


#include <TermQuery.h>

using namespace std;


class FuzzyQuery : public TermQuery {
public:
	FuzzyQuery(const string &field, const string &term) 
		: TermQuery(field, term) {}
	virtual string toString() const;
};

#endif
