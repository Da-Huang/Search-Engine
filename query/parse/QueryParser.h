#ifndef _QUERY_PARSER_H_
#define _QUERY_PARSER_H_

#include <Query.h>
#include <Analyzer.h>


/** The Result Need to be Deleted! **/
class QueryParser {
public:
	/** The original query would deleted in this method. **/
	static const Query* optimize(const Query *query);

	static const Query *parse(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer);

	static const Query *parseBool(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer);

	static const Query *parsePhrase(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer);
};


#endif
