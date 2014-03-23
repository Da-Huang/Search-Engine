#include <cassert>
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
	size_t status;
	status = fread(&docID, sizeof(docID), 1, fp);
	assert (status == 1);
	Posting res(docID);

	size_t posListSize;
	status = fread(&posListSize, sizeof(posListSize), 1, fp);
	assert (status == 1);
	for (size_t i = 0; i < posListSize; i ++) {
		size_t pos;
		status = fread(&pos, sizeof(pos), 1, fp);
		assert (status == 1);
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
	size_t status;
	status = fread(&docID, sizeof(docID), 1, fp);
	assert (status == 1);
	size_t posListSize;
	status = fread(&posListSize, sizeof(posListSize), 1, fp);
	assert (status == 1);
	fseek(fp, posListSize * sizeof(size_t), SEEK_CUR);
	current = ftell(fp);
	return docID;
}

size_t TmpPostingStream::peekDocID() {
	fseek(fp, current, SEEK_SET);
	size_t docID;
	size_t status = fread(&docID, sizeof(docID), 1, fp);
	assert (status == 1);
	return docID;
}

TmpPostingStream::~TmpPostingStream() {
	fclose(fp);
}


