#include <utility>
#include <algorithm>
#include <AndQuery.h>


AndQuery::AndQuery(const Query &q1, const Query &q2) {
	add(q1);
	add(q2);
}

class LessQuery {
public:
	bool operator () (
			const pair<const Query*, vector<ScoreDoc>> &q1,
			const pair<const Query*, vector<ScoreDoc>> &q2) const {
		return q1.second.size() < q2.second.size();
	}
};

vector<ScoreDoc> AndQuery::search(IndexSearcher &is) const {
	
	vector<pair<const Query*, vector<ScoreDoc>>> qs;
	for (size_t i = 0; i < queries.size(); i ++) {
		qs.push_back(make_pair(queries[i], queries[i]->search(is)));
	}
//	sort(qs.begin(), qs.end());
	return vector<ScoreDoc>();
}

string AndQuery::toString() const {
	string res = "(";
	for (auto it = queries.cbegin(); it != queries.cend(); it ++) {
		res += (*it)->toString();
		res += " & ";
	}
	if ( res.length() > 1 ) res.erase(res.length() - 3);
	res += ")";
	return res;
}

AndQuery::~AndQuery() {
	for (size_t i = 0; i < queries.size(); i ++)
		if ( (size_t)&i > (size_t)queries[i] ) delete queries[i];
}


