#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include <istream>
#include <sstream>
#include <cassert>
#include <Field.h>
#include <Analyzer.h>

using namespace std;

class TextField : public Field {
private:
	istream &in;
	const Analyzer &analyzer;

	size_t dl;
	bool dlValid;
public:
	TextField(const string &fieldName, 
			istream &in, const Analyzer &analyzer) 
		: Field(fieldName), in(in), analyzer(analyzer), dl(0),
			dlValid(false) {}

	TextField(const string &fieldName,
			const string &str, const Analyzer &analyzer) 
		: Field(fieldName), in(*new istringstream(str)), 
			analyzer(analyzer), dl(0), dlValid(false) {}

	virtual void writeTo(MMIndex &mmIndex, 
			const FieldNameMap &fieldNameMap, size_t docID);
	virtual inline string get() const { 
		throw string("Method 'get' is not supported in TextField."); 
	}
	virtual inline size_t getDL() const { 
		assert (dlValid); 
		return dl;
	};
	virtual ~TextField();
	virtual string toString() const;
};


#endif
