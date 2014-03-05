#include <WSTokenStream.h>


WSTokenStream::WSTokenStream(istream &in) : TokenStream(in) {
	while ( !in.eof() && in.peek() == ' ' ) in.get();
}

bool WSTokenStream::hasNext() const {
	return in;
}

Token WSTokenStream::next() {
	string str;
	size_t begin, end;
	if ( !in.eof() ) {
		begin = (size_t) in.tellg();
		str.push_back(in.get());
		while ( !in.eof() && in.peek() != ' ' )
			str.push_back(in.get());
		end = in.tellg();

		while ( !in.eof() && in.peek() == ' ' ) in.get();
	}
	return Token(str, begin, end);
}


