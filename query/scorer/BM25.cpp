#include <cmath>
#include <BM25.h>


double BM25::R(size_t tf, size_t dl, double avgdl) {
	const double K = k1 * (1 - b + b * dl / avgdl);
	return tf * (k1 + 1) / (tf + K);
}

double BM25::idf(size_t df, size_t DOC_NUM) {
	return log(1 +
			(DOC_NUM - df + double(0.5)) / 
			(df + double(0.5))
	);
	return 0;
}

double BM25::score(size_t df, size_t DOC_NUM, 
		size_t tf, size_t dl, double avgdl) {
//	return tf;
	return idf(df, DOC_NUM) * R(tf, dl, avgdl);
}


