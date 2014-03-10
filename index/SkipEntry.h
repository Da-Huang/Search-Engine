#ifndef _SKIP_ENTRY_H_
#define _SKIP_ENTRY_H_

#include <iostream>
#include <string>

using namespace std;


struct SkipEntry {
	size_t docID;
	size_t skipTo;

	string toString() const;
	void writeTo(ostream &out) const;
	void read(istream &in) const;
};

#endif
