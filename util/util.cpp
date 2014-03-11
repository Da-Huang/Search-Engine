#include <util.h>
#include <string.h>
extern int stemk(char *p, int i, int j);
namespace util {


string trim(const string &str) {
	size_t posL = str.find_first_not_of(' ');
	if ( posL == string::npos ) return string();
	size_t posR = str.find_last_not_of(' ');
	return str.substr(posL, posR - posL + 1);
}

string stem(const string &str) {
	char *p = strdup(str.c_str());
	int j = stemk(p, 0, (int) str.length() - 1);
	p[j + 1] = 0;
	string res(p);
	delete p;
	return res;
}


}
