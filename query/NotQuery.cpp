#include <NotQuery.h>


string NotQuery::toString() const {
	string res = "!";
	res += this->query.toString();
	return res;
}

vector<ScoreDoc> NotQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> notRes = query.search(is);
	vector<ScoreDoc> res;
	size_t i = 1, j = 0;
	while ( i <= is.docDB->getDocNum() && j < notRes.size() ) {
		if ( i == notRes[j].id() ) {
			i ++;
			j ++;

		} else if ( i < notRes[j].id() ) {
			res.push_back(ScoreDoc(i, boost));
			i ++;

		} else j ++;
	}
	while ( i <= is.docDB->getDocNum() ) {
		res.push_back(ScoreDoc(i, boost));
		i ++;
	}
	return res;
}

NotQuery::~NotQuery() {
	size_t i;
	if ( size_t(&i) > size_t(&query) ) delete &query;
}


