#include <MMIndex.h>


void MMIndex::add(const string &term, const Posting &posting) {
	vector<Posting> &postingList = index[term];
	const size_t N = postingList.size();
	if ( postingList[N - 1].docID == posting.docID )
		postingList[N - 1].merge(posting);
	else 
		postingList.push_back(posting);
}

void MMIndex::writeTo(ostream &indexOut, 
		ostream &termOut, ostream &postingOut) const {
	for (auto it = index.begin(); it != index.end(); it ++) {
		size_t termBegin = termOut.tellp();
		indexOut.write((char*)&termBegin, sizeof(termBegin));
		termOut.write(it->first.c_str(), it->first.length() + 1);
		const vector<Posting> &postingList = it->second;
		for (size_t i = 0; i < postingList.size(); i ++) {
			size_t postingListBegin = postingOut.tellp();
			indexOut.write(
					(char*)&postingListBegin, sizeof(postingListBegin));
			size_t postingListSize = postingList.size();
			indexOut.write(
					(char*)&postingListSize, sizeof(postingListSize));
			postingList[i].writeTo(postingOut);
		}
	}
}

MMIndex::~MMIndex() {
}


