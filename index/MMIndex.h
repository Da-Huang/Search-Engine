#ifndef _MM_INDEX_H_
#define _MM_INDEX_H_

#include <set>
#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <Posting.h>
//#include <IndexWriter.h>

using namespace std;

/*********************
  * Main Memory Index.
  ********************/
class MMIndex {
private:
	map<string, map<size_t, vector<Posting>>> index;
	size_t sizeByte;
public:
	MMIndex() : sizeByte(0) {}
	virtual void add(const string &term, 
			size_t fieldID, const Posting &posting);
	void writeTo(ostream &idxOut, ostream &fldOut, 
			ostream &trmOut, ostream &pstOut, size_t fieldNum) const;
	virtual void reset();
	virtual string toString() const;
	virtual ~MMIndex();
	inline virtual size_t size() const { return sizeByte; }
};

#endif
