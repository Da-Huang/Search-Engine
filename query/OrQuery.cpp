#include <utility>
#include <algorithm>
#include <OrQuery.h>


OrQuery::OrQuery(const Query &q1, const Query &q2) {
	add(q1);
	add(q2);
}

vector<ScoreDoc> OrQuery::search(IndexSearcher &is) const {
	if ( queries.size() == 0 ) return vector<ScoreDoc>();

	vector<pair<size_t, size_t>> querySeq;
	vector<vector<ScoreDoc>> allRes;
	for (size_t i = 0; i < queries.size(); i ++) {
		allRes.push_back(queries[i]->search(is));
		querySeq.push_back(make_pair(allRes[allRes.size() - 1].size(), i));
	}
	sort(querySeq.begin(), querySeq.end());

	vector<ScoreDoc> res = allRes[querySeq[0].second];
	for (size_t i = 1; i < querySeq.size(); i ++)
		res = merge(res, allRes[querySeq[i].second]);
	
	return res;
}

vector<ScoreDoc> OrQuery::merge(
		const vector<ScoreDoc> &docs1, const vector<ScoreDoc> &docs2) {
	vector<ScoreDoc> res;
	size_t i = 0, j = 0;
	while ( i < docs1.size() && j < docs2.size() ) {
		if ( docs1[i].id() < docs2[j].id() ) i ++;
		else if ( docs1[i].id() > docs2[j].id() ) j ++;
		else {
			res.push_back(docs1[i]);
			i ++; j ++;
		}
	}
	return res;
}

string OrQuery::toString() const {
	string res = "(";
	for (auto it = queries.cbegin(); it != queries.cend(); it ++) {
		res += (*it)->toString();
		res += " | ";
	}
	if ( res.length() > 1 ) res.erase(res.length() - 3);
	res += ")";
	return res;
}

OrQuery::~OrQuery() {
	for (size_t i = 0; i < queries.size(); i ++)
		if ( (size_t)&i > (size_t)queries[i] ) delete queries[i];
}


