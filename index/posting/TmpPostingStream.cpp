#include <util.h>
#include <IndexSearcher.h>
#include <TmpPostingStream.h>


void TmpPostingStream::write(const Posting &posting, double score) {
//	cout << "tmp: " << baseDocID << endl;
	posting.writeTo(fp, score, baseDocID);
	baseDocID = posting.getDocID();
	end = ftell(fp);
	df ++;
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
	/*size_t tf =*/ util::codec.decode(fp);
	size_t plBytes = util::codec.decode(fp);
//	cerr << "ps: pl= " << plBytes << endl;
	fseek(fp, plBytes, SEEK_CUR);
	current = ftell(fp);
	return docID;
}

tuple<size_t, size_t> TmpPostingStream::nextDocIDTF() {
	fseek(fp, current, SEEK_SET);
	size_t docID = util::codec.decode(fp) + 
			(util::codec.isDelta() ? baseDocID : 0);
	baseDocID = docID;
	size_t tf = util::codec.decode(fp);
	size_t plBytes = util::codec.decode(fp);
	fseek(fp, plBytes, SEEK_CUR);
	current = ftell(fp);
	return make_tuple(docID, tf);
}

size_t TmpPostingStream::peekDocID() {
	fseek(fp, current, SEEK_SET);
	size_t docID = util::codec.decode(fp) + 
			(util::codec.isDelta() ? baseDocID : 0);
	return docID;
}

double TmpPostingStream::peekScore(IndexSearcher &is, size_t fieldID) {
	// is and fieldID are useless
	fseek(fp, current, SEEK_SET);
	/*size_t docID =*/ util::codec.decode(fp) /*+ 
			(util::codec.isDelta() ? baseDocID : 0)*/;
	/*size_t tf =*/ util::codec.decode(fp);
	double score;
	size_t status = fread(&score, sizeof(score), 1, fp);
	assert (status == 1);
	return score;
}

TmpPostingStream::~TmpPostingStream() {
	fclose(fp);
}


