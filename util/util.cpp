#include <util.h>
namespace util {


string trim(const string &str) {
	size_t posL = str.find_first_not_of(' ');
	if ( posL == string::npos ) return string();
	size_t posR = str.find_last_not_of(' ');
	return str.substr(posL, posR - posL + 1);
}


}
