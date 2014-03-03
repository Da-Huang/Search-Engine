#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include <istream>
#include <sstream>
#include <Field.h>
#include <Analyzer.h>

using namespace std;

class TextField : public Field {
private:
	istream &in;
	const Analyzer &analyzer;
public:
	TextField(const string &fieldName, 
			istream &in, const Analyzer &analyzer) 
		: Field(fieldName), in(in), analyzer(analyzer) {}

	TextField(const string &fieldName,
			const string &str, const Analyzer &analyzer) 
		: Field(fieldName), in(*new istringstream(str)), 
		analyzer(analyzer) {}

	virtual void writeTo(MMIndex &mmIndex, 
			const map<string, size_t> &fieldIDMap, size_t docID) const;
	virtual ~TextField() {}
	virtual string toString() const;
};


#endif
