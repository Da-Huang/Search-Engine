#ifndef _QUERY_PARSER_H_
#define _QUERY_PARSER_H_

#include <Query.h>
#include <Analyzer.h>


/** The Result Need to be Deleted! **/
class QueryParser {
public:
	/** The original query would deleted in this method. **/
	static Query* optimize(const Query *query);

	static Query *parse(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer,
			bool fuzzy=false);

	static Query *parseBool(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer, 
			bool fuzzy=false);

	static Query *parsePhrase(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer,
			bool fuzzy=false);

	static Query *parseOr(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer,
			bool fuzzy=false);
};


#endif
