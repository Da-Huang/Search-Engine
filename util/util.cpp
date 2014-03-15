#include <algorithm>
#include <util.h>
#include <string.h>
extern int stemk(char *p, int i, int j);
namespace util {


string trim(const string &str) {
	size_t posL = str.find_first_not_of(' ');
	if ( posL == string::npos ) return string();
	size_t posR = str.find_last_not_of(' ');
	return str.substr(posL, posR - posL + 1);
}

string stem(const string &str) {
	char *p = strdup(str.c_str());
	int j = stemk(p, 0, (int) str.length() - 1);
	p[j + 1] = 0;
	string res(p);
	delete p;
	return res;
}

size_t editDistance(const string &str1, const string &str2) {
	const size_t M = str1.size();
	const size_t N = str2.size();
	size_t res[M + 1][N + 1];
	res[0][0] = 0;
	for (size_t i = 1; i <= M; i ++) res[i][0] = i;
	for (size_t j = 1; j <= N; j ++) res[0][j] = j;
	for (size_t i = 1; i <= M; i ++) {
		for (size_t j = 1; j <= N; j ++) {
			size_t d1 = res[i][j - 1] + 1;
			size_t d2 = res[i - 1][j] + 1;
			size_t d3 = res[i - 1][j - 1] + (str1[i] != str2[j]);
			res[i][j] = min({d1, d2, d3});
		}
	}
	return res[M][N];
}

}
