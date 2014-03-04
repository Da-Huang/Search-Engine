#ifndef _POSTING_H_
#define _POSTING_H_

#include <iostream>
#include <string>

using namespace std;

class Posting {
private:
	size_t docID;
//	vector<size_t> posList;	
public:
	Posting(size_t docID) : docID(docID) {}
	virtual inline size_t getDocID() const { return docID; }
	virtual void writeTo(ostream &out) const;
	virtual size_t merge(const Posting &posting);
	inline virtual size_t size() const { return sizeof(docID); }
	virtual string toString() const;
	virtual ~Posting() {}

	friend class MMIndex;
};

#endif
