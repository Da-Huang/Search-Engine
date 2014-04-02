#ifndef _BM25_H_
#define _BM25_H_

#include <cstddef>
using namespace std;


class BM25 {
private:
	static constexpr double k1 = 2;
	static constexpr double b = 0.75;
public:
	static double R(size_t tf, size_t dl, double avgdl);
	static double idf(size_t df, size_t DOC_NUM);
	static double score(size_t df, size_t DOC_NUM, 
			size_t tf, size_t dl, double avgdl);
};

#endif
