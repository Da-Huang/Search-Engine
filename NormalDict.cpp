#include "Dict.h"
#include <fstream>
#include <unordered_map>

using namespace std;


NormalDict::NormalDict(const string &filePath, bool isNew)
	: AbstractDict(filePath) {
	if ( !isNew ) {
		ifstream in(filePath);
		in >> *this;
		in.close();
	}
}

void NormalDict::add(const string &token) {
	auto it = dict.find(token);
	if ( it == dict.end() ) dict[token] = dict.size() + 1;
}

size_t NormalDict::getTokenID(const string &token) const {
	auto it = dict.find(token);
	return it == dict.end() ? 0 : it->second;
}

NormalDict::~NormalDict() {
	ofstream out(filePath);
	out << *this;
	out.close();
}


istream &operator >> (istream &in, NormalDict &dict) {
	return in;
}

ostream &operator << (ostream &out, const NormalDict &dict) {
	return out;
}

