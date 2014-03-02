#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include <Field.h>
#include <Analyzer.h>
#include <istream>
#include <sstream>
#include <string>
using namespace std;

class TextField : public Field {
private:
	istream &in;
	Analyzer &analyzer;
public:
	TextField(const string &fieldName, 
			istream &in, Analyzer &analyzer) 
		: Field(fieldName), in(in), analyzer(analyzer) {}

	TextField(const string &fieldName,
			const string &str, Analyzer &analyzer) 
		: Field(fieldName), in(*new istringstream(str)), 
		analyzer(analyzer) {}

	virtual ~TextField() {}
	virtual string toString() const;
};


#endif
