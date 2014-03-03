#include <TextField.h>
#include <TokenStream.h>
#include <Posting.h>

void TextField::writeTo(MMIndex &mmIndex, size_t docID) const {
	TokenStream ts = analyzer.tokenStream(in);
	while ( ts.hasNext() ) {
		Token token = ts.next();
		mmIndex.add(token.value, fieldName, Posting(docID));
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


