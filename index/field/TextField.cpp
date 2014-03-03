#include <TextField.h>
#include <TokenStream.h>
#include <Posting.h>
#include <MMIndex.h>

void TextField::writeTo(MMIndex &mmIndex, 
		const map<string, size_t> &fieldIDMap, size_t docID) const {
	auto it = fieldIDMap.find(fieldName);
	if ( it == fieldIDMap.end() ) return;

	TokenStream ts = analyzer.tokenStream(in);
	while ( ts.hasNext() ) {
		Token token = ts.next();
		mmIndex.add(token.value, it->second, Posting(docID));
	}
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


