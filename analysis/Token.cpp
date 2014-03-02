#include <Token.h>
#include <string>

using namespace std;

string Token::toString() const {
	string res = "<";
	res += value;
	res += ":";
	res += to_string(begin);
	res += ",";
	res += to_string(end);
	res += ">";
	return res;
}
