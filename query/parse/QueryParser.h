#ifndef _QUERY_PARSER_H_
#define _QUERY_PARSER_H_

#include <Query.h>
#include <Analyzer.h>


class QueryParser {
public:
	static const Query *parse(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer);
	/* The Result Need to be Deleted! */
	static const Query *parseBool(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer);
	static const Query *parsePhrase(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer);
};


#endif
