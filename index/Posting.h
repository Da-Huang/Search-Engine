#ifndef _POSTING_H_
#define _POSTING_H_

#include <ostream>

using namespace std;

class Posting {
public:
	size_t docID;
//	vector<size_t> posList;	
public:
	Posting(size_t docID) : docID(docID) {}
	virtual void writeTo(ostream &out) const;
	virtual size_t merge(const Posting &posting);
	inline virtual size_t size() const { return sizeof(docID); }
	virtual ~Posting() {}
};

#endif
