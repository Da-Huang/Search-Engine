#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <QueryParser.h>
#include <TermQuery.h>
#include <NotQuery.h>
#include <AndQuery.h>
#include <OrQuery.h>


const Query* QueryParser::parse(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer) {
	return parseBool(keywords, fieldName, analyzer);
}


const Query* QueryParser::parseBool(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer) {
	cerr << keywords << endl;
	map<string, size_t> priority;
	priority[")"] = 1;
	priority["|"] = 2;
	priority["&"] = 3;
	priority["!"] = 4;
	priority["("] = 5;
	priority[" "] = 6;
	stack<const Query*> s1;
	stack<string> s2;

	istringstream istr(keywords);
	bool atEnd = false;
	TokenStream &ts = analyzer.tokenStream(istr);
	while ( ts.hasNext() && !atEnd ) {
		if ( !ts.hasNext() ) atEnd = true;
		Token token = atEnd ? Token(" ", 0, 0) : ts.next();
//		cerr << token.toString() << endl;
		auto it = priority.find(token.value);

		if ( it == priority.end() ) 
			s1.push(new TermQuery(fieldName, token.value));
		else {
			while ( !s2.empty() && priority[s2.top()] >= it->second ) {
				string op = s2.top();
				s2.pop();
				if ( s1.empty() ) continue;
				if ( op == "!" ) {
					const Query *q = new NotQuery(*s1.top());
					s1.pop();
					s1.push(q);

				} else if ( s1.size() <= 1 ) continue;
				else if ( op == "&" ) {
					const Query *q1 = s1.top();
					s1.pop();
					const Query *q2 = s1.top();
					s1.pop();
					const Query *q = new AndQuery(*q1, *q2);
					s1.push(q);

				} else if ( op == "|" ) {
					const Query *q1 = s1.top();
					s1.pop();
					const Query *q2 = s1.top();
					s1.pop();
					const Query *q = new OrQuery(*q1, *q2);
					s1.push(q);
				}
			}
			s2.push(it->first);
		}
	}
	delete &ts;
	return s1.empty() ? NULL : s1.top();
}


const Query* QueryParser::parsePhrase(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer) {
	return NULL;
}


