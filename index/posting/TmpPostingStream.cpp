#include <TmpPostingStream.h>


void TmpPostingStream::write(const Posting &posting) {
	posting.writeTo(fp);
	end = ftell(fp);
}

/*
void TmpPostingStream::rewind() {
	current = 0;
}
*/

Posting TmpPostingStream::next() {
	fseek(fp, current, SEEK_SET);
	size_t docID;
	fread(&docID, sizeof(docID), 1, fp);
	Posting res(docID);

	size_t posListSize;
	fread(&posListSize, sizeof(posListSize), 1, fp);
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos;
		fread(&pos, sizeof(pos), 1, fp);
		res.addPos(pos);
	}
	current = ftell(fp);
	return res;
}

Posting TmpPostingStream::peek() {
	size_t current = this->current;
	Posting posting = next();
	this->current = current;
	return posting;
}

size_t TmpPostingStream::nextDocID() {
	fseek(fp, current, SEEK_SET);
	size_t docID;
	fread(&docID, sizeof(docID), 1, fp);
	size_t posListSize;
	fread(&posListSize, sizeof(posListSize), 1, fp);
	fseek(fp, posListSize * sizeof(size_t), SEEK_CUR);
	current = ftell(fp);
	return docID;
}

size_t TmpPostingStream::peekDocID() {
	fseek(fp, current, SEEK_SET);
	size_t docID;
	fread(&docID, sizeof(docID), 1, fp);
	return docID;
}

TmpPostingStream::~TmpPostingStream() {
	fclose(fp);
}


