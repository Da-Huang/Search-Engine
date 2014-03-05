#include <OrQuery.h>


vector<ScoreDoc> OrQuery::search(IndexSearcher &is) const {
	return vector<ScoreDoc>();
}

string OrQuery::toString() const {
	string res = "(";
	for (auto it = queries.cbegin(); it != queries.cend(); it ++) {
		res += (*it)->toString();
		res += " & ";
	}
	if ( res.length() > 1 ) res.erase(res.length() - 3);
	res += ")";
	return res;
}

OrQuery::~OrQuery() {
	for (size_t i = 0; i < queries.size(); i ++)
		if ( (size_t)&i > (size_t)queries[i] ) delete queries[i];
}


