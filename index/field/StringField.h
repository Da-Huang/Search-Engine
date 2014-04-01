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
			const FieldNameMap &fieldNameMap, size_t docID);
	virtual void save(ostream &cntOut, size_t fieldID) const;
	virtual inline size_t length() const { return str.length() + 1; }
	virtual string toString() const;
	virtual inline string get() const { return str; }
	virtual ~StringField() {}
};


#endif
