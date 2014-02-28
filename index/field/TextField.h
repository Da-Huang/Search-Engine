#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_

#include <istream>
using namespace std;

class TextField : public TextField {
private:
	string text;
	istream in;
};

#endif
