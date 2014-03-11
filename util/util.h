#ifndef _UTIL_H_
#define _UTIL_H_

namespace util {

template <typename T>
T delta(T a, T b) {
	return a < b ? b - a : a - b;
}



}
#endif
