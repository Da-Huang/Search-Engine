#include <FuzzyQuery.h>


string FuzzyQuery::toString() const {
	string res;
	res += field;
	res += ":f\"";
	res += term;
	res += "\"";
	return res;
}


