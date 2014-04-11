#include <cmath>
#include <cctype>
#include <algorithm>
#include <Snippet.h>


pair<size_t, size_t> Snippet::snippet(const map<string, double> &terms,
		const vector<Token> &tokens, size_t WIDTH) {

	map<string, size_t> termsCount;

	double score = 0;
	double bestScore = 0;
	size_t begin = 0, end = 0;
	size_t bestBegin = 0, bestEnd = 0;
	while ( end < tokens.size() ) {
#ifdef _DEBUG_SNIPPET_	
		fprintf(stderr, "tokens[begin=%ld]=%s(%ld-%ld), tokens[end=%ld]=%s(%ld-%ld), width=%ld\n", 
				begin, tokens[begin].value.c_str(), tokens[begin].begin, tokens[begin].end,
				end, tokens[end].value.c_str(), tokens[end].begin, tokens[end].end,
				tokens[end].end - tokens[begin].begin
				);
#endif
		if ( tokens[end].end - tokens[begin].begin <= WIDTH ) {
			auto it = terms.find(tokens[end].value);
			if ( it != terms.end() ) {
				auto countIt = termsCount.find(it->first);
				if ( countIt == termsCount.end() )
					termsCount[it->first] = 1;
				else countIt->second ++;
#ifdef _DEBUG_SNIPPET_	
				fprintf(stderr, "%lf ", score);
#endif

				score += it->second / exp(double(termsCount[it->first] - 1));
#ifdef _DEBUG_SNIPPET_	
				fprintf(stderr, "%lf:%ld\n", it->second, termsCount[it->first]);
				fprintf(stderr, "score += %lf = %lf\n", it->second / exp(double(termsCount[it->first] - 1)), score);
#endif
			}
			end ++;

		} else if ( begin < end ) {
			auto it = terms.find(tokens[begin].value);
			if ( it != terms.end() ) {
				size_t count = termsCount[it->first] --;
#ifdef _DEBUG_SNIPPET_	
				fprintf(stderr, "%lf -> ", score);
#endif
				score -= it->second / exp(double(count - 1));
#ifdef _DEBUG_SNIPPET_	
				fprintf(stderr, "%lf\n", score);
#endif
			}
			begin ++;

		} else {
			begin ++;
			end ++;
		}
		if ( score > bestScore ) {
			bestScore = score;
			bestBegin = begin;
			bestEnd = end;
		}
	}
	return make_pair(bestBegin, bestEnd);
}

string Snippet::snippet(const map<string, double> &terms,
		istream &in, size_t WIDTH, const Analyzer &analyzer) {

	vector<Token> tokens;
	TokenStream &ts = analyzer.tokenStream(in);
	while ( ts.hasNext() ) {
		Token token = ts.next();
		tokens.push_back(token);
	}
	delete &ts;

	auto pos = snippet(terms, tokens, WIDTH);
	size_t begin = pos.first, end = pos.second;
	if ( begin == end ) return fetch(in, 0, WIDTH);
	while ( begin > 0 && 
			tokens[end - 1].end - tokens[begin - 1].begin < WIDTH + 15 )
		begin --;
	while ( end < tokens.size() &&
			tokens[end].end - tokens[begin].begin < WIDTH + 30 )
		end ++;
	return fetch(in, tokens[begin].begin, tokens[end - 1].end);
}

string Snippet::fetch(istream &in, size_t begin, size_t end) {
	in.seekg(0, ios::end);
	end = min(size_t(in.tellg()), end);
	in.seekg(begin);
	string res;
	while ( size_t(in.tellg()) < end ) {
		char c = in.get();
		if ( isspace(c) ) {
			if ( res.length() > 0 && res[res.length() - 1] != ' ' )
				res.push_back(' ');
		} else {
			res.push_back(c);
		}
	}
	return res;
}


