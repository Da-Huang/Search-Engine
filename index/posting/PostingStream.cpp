#include <PostingStream.h>


PostingStream::PostingStream(istream &in, size_t begin, size_t end)
	: in(in), begin(begin), end(end), current(begin) {
	in.seekg(end);
	size_t skipsNum;
	in.read((char*)&skipsNum, sizeof(skipsNum));
	for (size_t i = 0; i < skipsNum; i ++) {
		skips.push_back(SkipEntry(in));
	}
}

Posting	PostingStream::next() {
	in.seekg(current);
	size_t docID;
	in.read((char*)&docID, sizeof(docID));
	Posting res(docID);

	size_t posListSize;
	in.read((char*)&posListSize, sizeof(posListSize));
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos;
		in.read((char*)&pos, sizeof(pos));
		res.pushPos(pos);
	}
	current = in.tellg();
	return res;
}


