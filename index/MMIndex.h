#ifndef _MM_INDEX_H_
#define _MM_INDEX_H_

#include <set>
#include <map>
#include <vector>
#include <string>
#include <Posting.h>
#include <ostream>

using namespace std;

/*********************
  * Main Memory Index.
  ********************/
class MMIndex {
private:
	set<string> fields;
	map<string, map<string, vector<Posting>>> index;
	size_t sizeByte;
public:
	MMIndex() : sizeByte(0) {}
	virtual void add(const string &term, 
			const string &field, const Posting &posting);
	virtual void writeTo(ostream &indexOut, ostream &metaOut,
			ostream &termOut, ostream &postingOut) const;
	virtual void reset();
	virtual ~MMIndex();
	inline virtual size_t size() const { return sizeByte; }
};

#endif
