#ifndef _PHRASE_QUERY_H_
#define _PHRASE_QUERY_H_


#include <Query.h>


class PhraseQuery : public Query {
private:
	vector<string> terms;
	vector<size_t> nears;
public:
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	virtual ~PhraseQuery() {}
};


#endif
