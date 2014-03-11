#include <PhraseQuery.h>
#include <TmpPostingStream.h>
#include <util.h>


PhraseQuery::PhraseQuery(const string &field, const vector<string> &terms, 
		const vector<size_t> &slops) 
	: field(field) , terms(terms), slops(slops) {
	if ( this->slops.size() == 0 && this->terms.size() > 1 ) 
		this->slops.push_back(5);
	while ( this->slops.size() + 1 < this->terms.size() ) {
		this->slops.push_back(this->slops.back());
	}
}

vector<ScoreDoc> PhraseQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> res;
	if ( terms.size() == 0 ) return res;

	size_t fieldID = is.fieldNameMap->getFieldID(field);
	PostingStream *ps = is.fileIndex->fetchPostingStream(fieldID, terms[0]);
	if ( ps == NULL ) return res;

	for (size_t i = 1; i < terms.size(); i ++) {
		PostingStream *ps1 = ps;
		PostingStream *ps2 = is.fileIndex->
			fetchPostingStream(fieldID, terms[i]);
		if ( ps2 == NULL ) {
			delete ps;
			return res;
		}
		ps = intersect(ps1, ps2, slops[i - 1]);
		delete ps1;
		delete ps2;
	}

	while ( ps->hasNext() ) {
		res.push_back(ScoreDoc(ps->nextDocID()));
	}
	delete ps;
	
	return res;
}

PostingStream* PhraseQuery::intersect(
		PostingStream *ps1, PostingStream *ps2, size_t slop) {
	PostingStream *ps = new TmpPostingStream();
	while ( ps1->hasNext() && ps2->hasNext() ) {
		size_t docID1 = ps1->peekDocID();
		size_t docID2 = ps2->peekDocID();
//		cout << docID1 << "," << docID2 << endl;
		if ( docID1 < docID2 ) {
			ps1->nextDocID();

		} else if ( docID1 > docID2 ) {
			ps2->nextDocID();

		} else {
			Posting posting(docID1);
			Posting p1 = ps1->next();
			Posting p2 = ps2->next();
//			cout << p1.toString() << "::" << p2.toString() << endl;
			vector<size_t> &posList1 = p1.posList;
			vector<size_t> &posList2 = p2.posList;
			size_t i = 0, j = 0;
			while ( i < posList1.size() && j < posList2.size() ) {
				size_t pos1 = posList1[i];
				size_t pos2 = posList2[j];
				size_t dpos = util::delta(pos1 + 1, pos2);
//				cout << dpos << endl;
				if ( dpos <= slop ) {
//					cout << "pos: " << pos2 << endl;
					posting.addPos(pos2);
					j ++;

				} else if ( pos1 < pos2 ) {
					i ++;
				} else { // pos1 > pos2
					j ++;
				}
			}
			// No need to do more as it's PhraseQuery
			
			if ( posting.posList.size() > 0 )
				((TmpPostingStream*)ps)->write(posting);
		}
	}
	return ps;
}

string PhraseQuery::toString() const {
	string res = field;
	res += ":<";
	if ( terms.size() > 0 ) {
		res += terms[0];
		for (size_t i = 1; i < terms.size(); i ++) {
			res += " ~";
			res += to_string(slops[i - 1]);
			res += "~ ";
			res += terms[i];
		}
	}
	res += ">";
	return res;
}


