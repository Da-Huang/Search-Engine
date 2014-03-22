#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
namespace util {
using namespace std;

template <typename T>
T delta(T a, T b) {
	return a < b ? b - a : a - b;
}

size_t MBtoB(size_t value);
string trim(const string &str);
//string stem(const string &str);
string stem(const string &str);
size_t editDistance(const string &str1, const string &str2);



}
#endif
