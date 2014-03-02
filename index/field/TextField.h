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
	const Analyzer &analyzer;
public:
	TextField(const string &fieldName, 
			istream &in, const Analyzer &analyzer) :
		Field(fieldName), in(in), analyzer(analyzer) {}
	TextField(const string &fieldName,
			const string &str, const Analyzer &analyzer) :
		Field(fieldName), in(*new istringstream(str)), analyzer(analyzer) {}
	~TextField() { delete &in; }
	virtual string toString() const;
};


#endif
