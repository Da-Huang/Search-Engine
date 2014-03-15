#include <FuzzyQuery.h>


vector<ScoreDoc> FuzzyQuery::search(IndexSearcher &is) const {
	return TermQuery::search(is);
}

PostingStream* FuzzyQuery::fetchPostingStream(IndexSearcher &is) const {
	return TermQuery::fetchPostingStream(is);
}

string FuzzyQuery::toString() const {
	string res;
	res += field;
	res += ":f\"";
	res += term;
	res += "\"";
	return res;
}


