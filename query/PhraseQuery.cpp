#include <cmath>
#include <util.h>
#include <FuzzyQuery.h>
#include <PhraseQuery.h>
#include <TmpPostingStream.h>


PhraseQuery::PhraseQuery(const string &field, const vector<string> &terms, 
			const vector<size_t> &slops, bool fuzzy) : slops(slops) {
	for (size_t i = 0; i < terms.size(); i ++)
		this->terms.push_back(fuzzy ?
				new FuzzyQuery(field, terms[i]) :
				new TermQuery(field, terms[i]));
	fillSlops();
}

PhraseQuery::PhraseQuery(
		const vector<TermQuery*> &terms, const vector<size_t> &slops) 
	: terms(terms), slops(slops) {
	fillSlops();
}

void PhraseQuery::fillSlops() {
	if ( slops.size() == 0 && terms.size() > 1 ) 
		slops.push_back(5);
	while ( slops.size() + 1 < terms.size() )
		slops.push_back(slops.back());
}

vector<ScoreDoc> PhraseQuery::search(IndexSearcher &is) const {
	vector<ScoreDoc> res;
	if ( terms.size() == 0 ) return res;
	const size_t fieldID = is.fieldNameMap->getFieldID(terms[0]->field);

	PostingStream *ps = terms[0]->fetchPostingStream(is, fieldID);
	if ( ps == NULL ) return res;
//	cout << terms[0]->toString() << endl;
//	cout << ps->toString() << endl;

	for (size_t i = 1; i < terms.size(); i ++) {
		PostingStream *ps1 = ps;
//		cout << "ps1:" << ps1->toString() << endl;
//		cout << "ps1->hasNext:" << ps1->hasNext() << endl;
		if ( terms[i]->field != terms[0]->field ) {
			delete ps;
			return res;
		}
		PostingStream *ps2 = terms[i]->fetchPostingStream(is, fieldID);
//		cout << terms[i]->toString() << endl;
		if ( ps2 == NULL ) {
			delete ps;
			return res;
		}
//		cout << "ps2:" << ps2->toString() << endl;
		ps = intersect(ps1, ps2, slops[i - 1], is, fieldID);
//		cout << ps->toString() << endl;
		delete ps1;
		delete ps2;
	}

	res = ps->getScoreDocs(is, fieldID);
	delete ps;
	for (size_t i = 0; i < res.size(); i ++) res[i] *= boost;
	return res;
}

/** ps1 and ps2 must *not* be NULL **/
PostingStream* PhraseQuery::intersect(
		PostingStream *ps1, PostingStream *ps2, size_t slop, 
		IndexSearcher &is, size_t fieldID) {
//	cout << "=============" << endl;
//	cout << ps1->toString() << endl;
//	cout << ps2->toString() << endl;
//	cout << "=============" << endl;
	PostingStream *ps = new TmpPostingStream();
	while ( ps1->hasNext() && ps2->hasNext() ) {
		const size_t docID1 = ps1->peekDocID();
		const size_t docID2 = ps2->peekDocID();
//		cout << docID1 << "," << docID2 << endl;
		if ( docID1 < docID2 ) {
			ps1->nextDocID();

		} else if ( docID1 > docID2 ) {
			ps2->nextDocID();

		} else {
			Posting posting(docID1);
			const double score1 = ps1->peekScore(is, fieldID);
			const double score2 = ps2->peekScore(is, fieldID);
			const double score  = score1 + score2;
			Posting p1 = ps1->next();
			Posting p2 = ps2->next();
//			cout << p1.toString() << "::" << p2.toString() << endl;
			vector<size_t> &posList1 = p1.posList;
			vector<size_t> &posList2 = p2.posList;
			size_t i = 0, j = 0;
			while ( i < posList1.size() && j < posList2.size() ) {
				const size_t pos1 = posList1[i];
				const size_t pos2 = posList2[j];
				const size_t dpos = util::delta(pos1 + 1, pos2);
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
				ps->write(posting, score);
		}
	}
//	cout << ps->toString() << endl;
//	cout << "end" << endl;
	ps->rewind();
	return ps;
}

string PhraseQuery::toString() const {
	string res = "p<";
	if ( terms.size() > 0 ) {
		res += terms[0]->toString();
		for (size_t i = 1; i < terms.size(); i ++) {
			res += " \\";
			res += to_string(slops[i - 1]);
			res += " ";
			res += terms[i]->toString();
		}
	}
	res += ">";
	return res;
}

PhraseQuery::~PhraseQuery() {
	for (size_t i = 0; i < terms.size(); i ++)
		if ( size_t(&i) > size_t(terms[i]) ) delete terms[i];
}


