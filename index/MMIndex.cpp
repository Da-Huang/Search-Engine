#include <iostream>
#include <MMIndex.h>


void MMIndex::add(const string &term, 
		size_t fieldID, const Posting &posting) {
	vector<Posting> &postingList = index[term][fieldID];
	const size_t N = postingList.size();

	if ( N > 0 && postingList[N - 1].docID == posting.docID ) {
		sizeByte += postingList[N - 1].merge(posting);
	} else {
		postingList.push_back(posting);
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
			auto postingListIt = termIt->second.find(fieldIt);
			size_t fieldBegin = pstOut.tellp();
			idxOut.write((char*)&fieldBegin, sizeof(fieldBegin));
			if ( postingListIt == termIt->second.end() ) {
				size_t fieldSize = 0;
				idxOut.write((char*)&fieldSize, sizeof(fieldSize));
				continue;
			}

			const vector<Posting> &postingList = postingListIt->second;
			size_t fieldSize = postingList.size();
			idxOut.write((char*)&fieldSize, sizeof(fieldSize));

			/* Write each posting. */
			for (auto postingIt = postingList.begin(); 
					postingIt != postingList.end(); postingIt ++) {
				postingIt->writeTo(pstOut);
			}
		}
	}
}

void MMIndex::reset() {
	index.clear();
	sizeByte = 0;
}

MMIndex::~MMIndex() {
	cerr << toString() << endl;
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
			if ( res[res.length() - 1] == ',' ) res.erase(res.length() - 1);
			res += "],";
		}
		if ( res[res.length() - 1] == ',' ) res.erase(res.length() - 1);
		res += "\n";
	}
	return res;
}

