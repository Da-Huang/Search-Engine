#ifndef _FUZZY_QUERY_H_
#define _FUZZY_QUERY_H_


#include <map>
#include <tuple>
#include <vector>
#include <TermQuery.h>

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
	virtual tuple<size_t, size_t> fetchScope(IndexSearcher &is, 
			size_t fieldID) const;
	virtual vector<PostingStream*> fetchPostingStreams(
			IndexSearcher &is, size_t fieldID,
			map<PostingStream*, double> &boosts) const;
	virtual map<string, double> fetchScoreTerms(IndexSearcher &is) const;
	virtual map<string, double> fetchScoreTerms(
			IndexSearcher &is, size_t fieldID) const;
	virtual string toString() const;
	virtual ~FuzzyQuery() {}
};

#endif
