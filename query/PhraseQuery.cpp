#include <PhraseQuery.h>


vector<ScoreDoc> PhraseQuery::search(IndexSearcher &is) const {
	return vector<ScoreDoc>();
}

string PhraseQuery::toString() const {
	return "";
}
