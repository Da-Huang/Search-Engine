#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <Field.h>
#include <string>
#include <map>

using namespace std;

class Document {
private:
	map<string, Field&> fields;
public:
	void addField(Field &field);
	virtual string toString() const;
	virtual ~Document() {}
};

#endif
