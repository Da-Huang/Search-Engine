#include <iostream>
#include <MMIndex.h>
#include <PostingStream.h>


void MMIndex::add(const string &term, size_t fieldID,
		size_t docID, size_t pos) {
	vector<Posting> &pstList = index[term][fieldID];
	const size_t N = pstList.size();
	if ( N > 0 && pstList[N - 1].docID == docID ) {
		pstList[N - 1].addPos(pos);
		sizeByte += sizeof(docID);
	} else {
		pstList.push_back(Posting(docID, pos));
		sizeByte += sizeof(docID) + sizeof(pos);
	}
}

void MMIndex::add(const string &term, 
		size_t fieldID, const Posting &posting) {
	vector<Posting> &pstList = index[term][fieldID];
	const size_t N = pstList.size();

	if ( N > 0 && pstList[N - 1].docID == posting.docID ) {
		sizeByte += pstList[N - 1].merge(posting);
	} else {
		pstList.push_back(posting);
		sizeByte += posting.size();
	}
}

void MMIndex::writeTo(ostream &idxOut, ostream &fldOut,
		ostream &trmOut, ostream &pstOut, size_t fieldNum) const {

	fldOut.write((char*)&fieldNum, sizeof(fieldNum));

	for (auto termIt = index.begin(); termIt != index.end(); termIt ++) {
		size_t termBegin = trmOut.tellp();
		idxOut.write((char*)&termBegin, sizeof(termBegin));
		trmOut.write(termIt->first.c_str(), termIt->first.length() + 1);

		/* Write each field. */
		for (size_t fieldIt = 1; fieldIt <= fieldNum; fieldIt ++) {
			auto pstListIt = termIt->second.find(fieldIt);
			if ( pstListIt == termIt->second.end() ) {
				size_t pstListBegin = pstOut.tellp();
				size_t pstListEnd = pstListBegin;
				idxOut.write((char*)&pstListBegin, sizeof(pstListBegin));
				idxOut.write((char*)&pstListEnd, sizeof(pstListEnd));
				continue;
			}

			PostingStream ps(pstOut, pstOut.tellp(), pstOut.tellp());

//			cout << termIt->first << endl;
			/* Write each posting. */
			const vector<Posting> &pstList = pstListIt->second;
			for (auto pstIt = pstList.begin(); 
					pstIt != pstList.end(); pstIt ++) {
//				cout << pstIt->toString() << endl;
				ps.write(*pstIt);
			}
			ps.writeSkips();

			size_t pstListBegin = ps.getBegin();
			size_t pstListEnd = ps.getEnd();
			idxOut.write((char*)&pstListBegin, sizeof(pstListBegin));
			idxOut.write((char*)&pstListEnd, sizeof(pstListEnd));
		}
	}
}

void MMIndex::reset() {
	index.clear();
	sizeByte = 0;
}

string MMIndex::toString() const {
	string res;
	for (auto idxIt = index.begin(); idxIt != index.end(); idxIt ++) {
		res += idxIt->first;
		res += ": ";
		for (auto pstIt = idxIt->second.begin();
				pstIt != idxIt->second.end(); pstIt ++) {
			res += to_string(pstIt->first);
			res += "'[";
			for (auto it = pstIt->second.begin();
					it != pstIt->second.end(); it ++) {
				res += it->toString();
				res += ",";
			}
			if ( res.back() == ',' ) res.erase(res.length() - 1);
			res += "],";
		}
		if ( res.back() == ',' ) res.erase(res.length() - 1);
		res += "\n";
	}
	return res;
}


