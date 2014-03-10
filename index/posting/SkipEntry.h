#ifndef _SKIP_ENTRY_H_
#define _SKIP_ENTRY_H_

#include <iostream>
#include <string>

using namespace std;


class SkipEntry {
public:
	size_t docID;
	size_t skipTo;

public:
	SkipEntry(size_t docID, size_t skipTo) : docID(docID), skipTo(skipTo) {}
	SkipEntry(istream &in) { read(in); }
	virtual string toString() const;
	virtual void writeTo(ostream &out) const;
	virtual void read(istream &in) const;
	virtual ~SkipEntry() {}
};


#endif
