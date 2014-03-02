#include <TextField.h>

string TextField::toString() const {
	string res = "<";
	res += fieldName;
	res += ",";
	ostringstream os;
	os << "istream:" << in;
	res += os.str();
	res += ">";
	return res;
}


