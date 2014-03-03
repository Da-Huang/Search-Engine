#ifndef _STRING_FIELD_H_
#define _STRING_FIELD_H_

#include <Field.h>
#include <string>
using namespace std;


class StringField : public Field {
private:
	string str;
public:
	StringField(const string &fieldName, const string &str) 
		: Field(fieldName), str(str) {}

	virtual void writeTo(MMIndex &mmIndex, size_t docID) const;
	virtual string toString() const;
	virtual ~StringField() {}
};


#endif
