#include <cassert>
#include <util.h>
#include <TmpPostingStream.h>


void TmpPostingStream::write(const Posting &posting) {
//	cout << "tmp: " << baseDocID << endl;
	posting.writeTo(fp, baseDocID);
	baseDocID = posting.getDocID();
	end = ftell(fp);
}

Posting TmpPostingStream::next() {
	fseek(fp, current, SEEK_SET);
	Posting res(fp, baseDocID);
	baseDocID = res.getDocID();
	current = ftell(fp);
	return res;
}

Posting TmpPostingStream::peek() {
	return Posting(fp, baseDocID);
}

size_t TmpPostingStream::nextDocID() {
	fseek(fp, current, SEEK_SET);
	size_t docID = util::codec.decode(fp) + 
			(util::codec.isDelta() ? baseDocID : 0);
	baseDocID = docID;
	/*size_t posListSize =*/ util::codec.decode(fp);
	size_t plBytes = util::codec.decode(fp);
//	cerr << "ps: pl= " << plBytes << endl;
	fseek(fp, plBytes, SEEK_CUR);
	current = ftell(fp);
	return docID;
}

size_t TmpPostingStream::peekDocID() {
	fseek(fp, current, SEEK_SET);
	size_t docID = util::codec.decode(fp) + 
			(util::codec.isDelta() ? baseDocID : 0);
	return docID;
}

TmpPostingStream::~TmpPostingStream() {
	fclose(fp);
}


