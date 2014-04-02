#include <Posting.h>
#include <MMIndex.h>
#include <TextField.h>
#include <TokenStream.h>
#include <FieldNameMap.h>


void TextField::writeTo(MMIndex &mmIndex, 
		const FieldNameMap &fieldNameMap, size_t docID) {
	size_t fieldID = fieldNameMap.getFieldID(fieldName);
	if ( fieldID == 0 ) return;

	dlValid = true;
	TokenStream &ts = analyzer.tokenStream(in);
	while ( ts.hasNext() ) {
		Token token = ts.next();
//		cerr << token.toString() << endl;
		mmIndex.add(token.value, fieldID, docID, token.pos);
		dl = token.pos;
	}
	delete &ts;
}

string TextField::toString() const {
	string res = "<";
	res += fieldName;
	res += ":";
	ostringstream os;
	os << "istream(" << in;
	res += os.str();
	res += ")>";
	return res;
}

TextField::~TextField() {
	size_t i;
	if ( size_t(&i) > size_t(&in) ) delete &in;
}


