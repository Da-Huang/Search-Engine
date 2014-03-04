#include <NotQuery.h>


vector<ScoreDoc> NotQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> notRes = query.search(is);
	vector<ScoreDoc> res;
	size_t i = 1, j = 0;
	while ( i <= is.docDB->getDocNum() && j < notRes.size() ) {
		if ( i == notRes[j].id() ) {
			i ++;
			j ++;

		} else if ( i < notRes[j].id() ) {
			res.push_back(ScoreDoc(i));
			i ++;

		} else j ++;
	}
	return res;
}
