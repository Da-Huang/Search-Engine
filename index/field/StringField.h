#ifndef _STRING_FIELD_H_
#define _STRING_FIELD_H_

#include <Field.h>


class StringField : public Field {
private:
	string str;
public:
	StringField(const string &fieldName, const string &str) 
		: Field(fieldName), str(str) {}

	virtual void writeTo(MMIndex &mmIndex, 
			const FieldNameMap &fieldNameMap, size_t docID) const;
	virtual string toString() const;
	virtual string get() const { return str; }
	virtual ~StringField() {}
};


#endif
