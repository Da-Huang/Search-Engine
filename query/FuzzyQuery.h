#ifndef _FUZZY_QUERY_H_
#define _FUZZY_QUERY_H_


#include <TermQuery.h>

using namespace std;


class FuzzyQuery : public TermQuery {
private:
	
public:
	FuzzyQuery(const string &field, const string &term) 
		: TermQuery(field, term) {}
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual PostingStream* fetchPostingStream(IndexSearcher &is) const;
	virtual string toString() const;
	virtual ~FuzzyQuery() {}
};

#endif
