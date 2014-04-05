#ifndef _FUZZY_QUERY_H_
#define _FUZZY_QUERY_H_


#include <TermQuery.h>
#include <vector>

using namespace std;


class FuzzyQuery : public TermQuery {
private:
	const size_t dis;
public:
	FuzzyQuery(const string &field, const string &term, size_t dis=2) 
		: TermQuery(field, term), dis(dis) {}
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual PostingStream* fetchPostingStream(IndexSearcher &is) const;
	virtual PostingStream* fetchPostingStream(IndexSearcher &is, 
			size_t fieldID) const;
	virtual vector<PostingStream*> fetchPostingStreams(
			IndexSearcher &is, size_t fieldID) const;
	virtual string toString() const;
	virtual ~FuzzyQuery() {}
};

#endif
