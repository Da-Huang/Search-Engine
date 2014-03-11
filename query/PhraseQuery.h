#ifndef _PHRASE_QUERY_H_
#define _PHRASE_QUERY_H_


#include <vector>
#include <Query.h>
#include <PostingStream.h>

using namespace std;


class PhraseQuery : public Query {
private:
	string field;
	vector<string> terms;
	vector<size_t> nears;

public:
	PhraseQuery(const string &field, const vector<string> &terms, 
			const vector<size_t> &nears);
	virtual vector<ScoreDoc> search(IndexSearcher &is) const;
	virtual string toString() const;
	static PostingStream* intersect(
			PostingStream *ps1, PostingStream *ps2, size_t near);
	virtual ~PhraseQuery() {}
};


#endif
