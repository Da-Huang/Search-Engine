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

void MMIndex::writeTo(ostream &indexOut, ostream &metaOut,
		ostream &termOut, ostream &postingOut, size_t fieldNum) const {

	metaOut.write((char*)&fieldNum, sizeof(fieldNum));

	for (auto termIt = index.begin(); termIt != index.end(); termIt ++) {
		size_t termBegin = termOut.tellp();
		indexOut.write((char*)&termBegin, sizeof(termBegin));
		termOut.write(termIt->first.c_str(), termIt->first.length() + 1);

		/* Write each field. */
		for (size_t fieldIt = 0; fieldIt < fieldNum; fieldIt ++) {
			auto postingListIt = termIt->second.find(fieldIt);
			size_t fieldBegin = termOut.tellp();
			indexOut.write((char*)&fieldBegin, sizeof(fieldBegin));
			if ( postingListIt == termIt->second.end() ) {
				size_t fieldSize = 0;
				indexOut.write((char*)&fieldSize, sizeof(fieldSize));
				continue;
			}

			const vector<Posting> &postingList = postingListIt->second;
			size_t fieldSize = postingList.size();
			indexOut.write((char*)&fieldSize, sizeof(fieldSize));

			/* Write each posting. */
			for (auto postingIt = postingList.begin(); 
					postingIt != postingList.end(); postingIt ++) {
				postingIt->writeTo(postingOut);
			}
		}
	}
}

void MMIndex::reset() {
	index.clear();
	sizeByte = 0;
}

MMIndex::~MMIndex() {
}


