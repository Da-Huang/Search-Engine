#ifndef _GREATER_POS_H_
#define _GREATER_POS_H_

#include <Posting.h>


class GreaterPos {
private:
	const vector<Posting> &pv;
	const vector<size_t> &index;
public:
	GreaterPos(const vector<Posting> &pv, const vector<size_t> &index) 
		: pv(pv), index(index) {}
	bool operator () (size_t i, size_t j) const {
		return pv[i].posList[index[i]] > pv[j].posList[index[j]];
	}
};

#endif
