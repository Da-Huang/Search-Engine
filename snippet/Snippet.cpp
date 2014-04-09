#include <vector>
#include <cassert>
#include <Snippet.h>


pair<size_t, size_t> Snippet::fetchSnippetPos(
		const map<string, double> &terms,
		istream &in, size_t width, const Analyzer &analyzer) {

	map<string, size_t> termsCount;
	vector<Token> tokens;
	size_t begin = 0, end = 0;
	TokenStream &ts = analyzer.tokenStream(in);
	while ( ts.hasNext() ) {
		Token token = ts.next();
		tokens.push_back(token);
		begin = token.begin;
		end = token.end;
	}
	delete &ts;
	return make_pair(begin, end);
}

string Snippet::snippet(const map<string, double> &terms,
		istream &in, size_t width, const Analyzer &analyzer) {

	auto pos = fetchSnippetPos(terms, in, width, analyzer);
	size_t begin = pos.first, end = pos.second;
	assert (end >= begin);
	in.seekg(begin);
	char snippetChars[end - begin];
	in.read(snippetChars, end - begin);
	return string(snippetChars, end - begin);
}


