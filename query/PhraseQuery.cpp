#include <PhraseQuery.h>


PhraseQuery::PhraseQuery(const string &field, const vector<string> &terms, 
		const vector<size_t> &nears) 
	: field(field) , terms(terms), nears(nears) {
	if ( this->nears.size() == 0 && this->terms.size() > 1 ) 
		this->nears.push_back(5);
	while ( this->nears.size() + 1 < this->terms.size() ) {
		this->nears.push_back(this->nears.back());
	}
}

vector<ScoreDoc> PhraseQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> res;

	if ( terms.size() == 0 ) return res;
	size_t fieldID = is.fieldNameMap->getFieldID(field);
	PostingStream *ps = is.fileIndex->fetchPostingStream(fieldID, terms[0]);

	while ( ps->hasNext() ) {
		res.push_back(ps->nextDocID());
	}
	
	return vector<ScoreDoc>();
}

string PhraseQuery::toString() const {
	string res = "<";
	if ( terms.size() > 0 ) {
		res += terms[0];
		for (size_t i = 1; i < terms.size(); i ++) {
			res += " ~";
			res += to_string(nears[i - 1]);
			res += "~ ";
			res += terms[i];
		}
	}
	res += ">";
	return res;
}


