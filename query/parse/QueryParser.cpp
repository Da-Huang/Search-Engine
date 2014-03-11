#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <QueryParser.h>
#include <TermQuery.h>
#include <NotQuery.h>
#include <AndQuery.h>
#include <OrQuery.h>
#include <PhraseQuery.h>


const Query* QueryParser::optimize(const Query *query) {
	if ( dynamic_cast<const PhraseQuery*>(query) )
		return new PhraseQuery((const PhraseQuery&)*query);
	if ( dynamic_cast<const TermQuery*>(query) )
		return new TermQuery((const TermQuery&)*query);
	if ( dynamic_cast<const NotQuery*>(query) )
		return new NotQuery(*optimize(&(((NotQuery*)query)->query)));
	if ( dynamic_cast<const AndQuery*>(query) ) {
		const AndQuery *caq = (const AndQuery*)query;
		AndQuery *aq = new AndQuery();
		for (size_t i = 0; i < caq->queries.size(); i ++) {
			const Query *subQuery = optimize(caq->queries[i]);
			if ( dynamic_cast<const AndQuery*>(subQuery) ) {
				const AndQuery *subAndQuery = (const AndQuery*)subQuery;
				aq->queries.insert(aq->queries.end(),
						subAndQuery->queries.cbegin(), 
						subAndQuery->queries.cend());
			} else {
				aq->queries.push_back(subQuery);
			}
		}
		return aq;
	}
	if ( dynamic_cast<const OrQuery*>(query) ) {
		const OrQuery *coq = (const OrQuery*)query;
		OrQuery *oq = new OrQuery();
		for (size_t i = 0; i < coq->queries.size(); i ++) {
			const Query *subQuery = optimize(coq->queries[i]);
			if ( dynamic_cast<const OrQuery*>(subQuery) ) {
				const OrQuery *subOrQuery = (const OrQuery*)subQuery;
				oq->queries.insert(oq->queries.end(),
						subOrQuery->queries.cbegin(), 
						subOrQuery->queries.cend());
			} else {
				oq->queries.push_back(subQuery);
			}
		}
		return oq;
	}
	return NULL;
}


const Query* QueryParser::parse(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer) {
	return parseBool(keywords, fieldName, analyzer);
}

const Query* QueryParser::parseBool(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer) {
//	cerr << keywords << endl;
	map<string, size_t> priority;
	priority[" "] = 0;
	priority[")"] = 1;
	priority["("] = 2;
	priority["|"] = 3;
	priority["&"] = 4;
	priority["!"] = 5;
	stack<const Query*> s1;
	stack<string> s2;

	istringstream istr(keywords);
	bool atEnd = false;
	TokenStream &ts = analyzer.tokenStream(istr);
	while ( ts.hasNext() || !atEnd ) {
		if ( !ts.hasNext() ) atEnd = true;
		Token token = atEnd ? Token(" ", 0, 0) : ts.next();
//		cerr << "token: " << token.toString() << endl;
//		cerr << "atEnd: " << atEnd << endl;
		auto it = priority.find(token.value);

		if ( it == priority.end() ) {
			s1.push(new TermQuery(fieldName, token.value));

		} else if ( it->first == "(" ) {
			s2.push(it->first);
//			cerr << "push op: " << it->first << endl;

		} else {
			while ( !s2.empty() && priority[s2.top()] >= it->second ) {
				string op = s2.top();
//				cerr << "while: " << op << endl;
				s2.pop();
				if ( s1.empty() ) continue;
				if ( op == "!" ) {
					const Query *q = new NotQuery(*s1.top());
					s1.pop();
					s1.push(q);

				} else if ( op == "(" ) {
					if ( it->first == ")" ) break;

				} else if ( s1.size() <= 1 ) continue;
				else if ( op == "&" ) {
					const Query *q1 = s1.top();
					s1.pop();
					const Query *q2 = s1.top();
					s1.pop();
					const Query *q = new AndQuery(*q2, *q1);
					s1.push(q);
//					cerr << "push: " << q->toString() << endl;

				} else if ( op == "|" ) {
					const Query *q1 = s1.top();
					s1.pop();
					const Query *q2 = s1.top();
					s1.pop();
					const Query *q = new OrQuery(*q2, *q1);
					s1.push(q);
//					cerr << "push: " << q->toString() << endl;

				}
			}
//			cerr << "push op: " << it->first << endl;
			if ( it->first != ")" ) s2.push(it->first);
		}
	}
	delete &ts;

	if ( s1.empty() ) return NULL;
	const Query *res = optimize(s1.top());
	while ( !s1.empty() ) {
		delete s1.top();
		s1.pop();
	}
	return res;
}


const Query* QueryParser::parsePhrase(const string &keywords, 
			const string &fieldName, const Analyzer &analyzer) {
	vector<string> terms;
	vector<size_t> nears;
	istringstream istr(keywords);
	TokenStream &ts = analyzer.tokenStream(istr);
	while ( ts.hasNext() ) {
		Token token = ts.next();
//		cout << token.toString() << endl;
		if ( token.value[0] == '~' ) {
			size_t near = stoi(token.value.substr(1));
			if ( terms.size() >= nears.size() + 1 )
				nears.push_back(near);

		} else {
			if ( terms.size() >= nears.size() + 1 ) {
				size_t near = 0;
				nears.push_back(near);
			}
			terms.push_back(token.value);
		}
	}
	
	return new PhraseQuery(fieldName, terms, nears);
}


