#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <map>
#include <string>
#include <Field.h>

using namespace std;

class Document {
private:
	map<string, Field&> fields;
public:
//	Field& getField(const string &fieldName);
	void addField(Field &field);
	virtual string toString() const;
	virtual ~Document();

	friend class IndexWriter;
};

#endif
