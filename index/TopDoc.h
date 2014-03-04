#ifndef _TOP_DOC_H_
#define _TOP_DOC_H_

#include <vector>
#include <ScoreDoc.h>

using namespace std;


class TopDoc {
public:
	size_t totalHits;
	vector<ScoreDoc> scoreDocs;

	TopDoc(size_t totalHits, const vector<ScoreDoc> &scoreDocs) 
		: totalHits(totalHits), scoreDocs(scoreDocs) {}
};

#endif
