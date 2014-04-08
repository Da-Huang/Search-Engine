#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <map>
#include <string>
#include <Field.h>

using namespace std;

class Document {
private:
	map<string, Field&> fields;
	double staticScore;
public:
	Document() : staticScore(0) {}
//	Field& getField(const string &fieldName);
	virtual string get(const string &fieldName) const;
	virtual inline double getStaticScore() const { return staticScore; }
	virtual inline void setStaticScore(double staticScore) { 
		this->staticScore = staticScore;
	}
	virtual void addField(Field &field);
	virtual string toString() const;
	virtual ~Document();

	friend class IndexWriter;
};

#endif
