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

void NormalDict::add(const string &term) {
	auto it = dict.find(term);
	if ( it == dict.end() ) dict[term] = dict.size() + 1;
}

size_t NormalDict::getTermID(const string &term) const {
	auto it = dict.find(term);
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

