#ifndef _TERM_QUERY_H_
#define _TERM_QUERY_H_

#include <Query.h>


class TermQuery : public Query {
protected:
	string field;
	string term;
public:
	TermQuery(const string &field, const string &term) 
		: field(field), term(term) {}
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual PostingStream* fetchPostingStream(IndexSearcher &is) const;
	virtual PostingStream* fetchPostingStream(
			IndexSearcher &is, size_t fieldID) const;
	virtual string toString() const;
	virtual ~TermQuery() {}

	friend class PhraseQuery;
};



#endif
