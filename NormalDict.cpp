#include "Dict.h"
#include <unordered_map>

using namespace std;

void NormalDict::add(const string &token) {
	auto it = dict.find(token);
	if ( it == dict.end() ) dict[token] = dict.size() + 1;
}

size_t NormalDict::getTokenID(const string &token) const {
	auto it = dict.find(token);
	return it == dict.end() ? 0 : it->second;
}

