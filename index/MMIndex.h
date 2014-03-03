#ifndef _MM_INDEX_H_
#define _MM_INDEX_H_

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
	map<string, vector<Posting>> index;
public:
	virtual void add(const string &term, const Posting &posting);
	virtual void writeTo(ostream &indexOut, 
			ostream &termOut, ostream &postingOut) const;
	virtual ~MMIndex();
};

#endif
