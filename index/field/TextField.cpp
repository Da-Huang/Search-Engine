#include <TextField.h>

void TextField::writeTo(MMIndex &mmIndex) const {
}

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


