#ifndef _PHRASE_QUERY_H_
#define _PHRASE_QUERY_H_


#include <vector>
#include <Query.h>
#include <TermQuery.h>
#include <PostingStream.h>

using namespace std;


class PhraseQuery : public Query {
private:
	vector<TermQuery*> terms;
	vector<size_t> slops;

	void fillSlops();
public:
	PhraseQuery(const string &field, const vector<string> &terms, 
			const vector<size_t> &slops, bool fuzzy=false);
	PhraseQuery(const vector<TermQuery*> &terms, 
			const vector<size_t> &slops);
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	static PostingStream* intersect(
			PostingStream *ps1, PostingStream *ps2, size_t slop,
			IndexSearcher &is, size_t fieldID);
	virtual map<string, double> fetchScoreTerms(IndexSearcher &is) const;
	virtual ~PhraseQuery();
};


#endif
