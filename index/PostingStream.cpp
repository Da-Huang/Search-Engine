#include <PostingStream.h>


PostingStream::PostingStream(istream &in, size_t begin, size_t end)
	: in(in), begin(begin), end(end), current(begin) {}

Posting	PostingStream::next() {
	in.seekg(current);
	size_t docID;
	in.read((char*)&docID, sizeof(docID));
	current = in.tellg();
	return Posting(docID);
}
