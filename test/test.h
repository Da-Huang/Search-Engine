#ifndef _TEST_H_
#define _TEST_H_

#include <string>

using namespace std;


namespace test {

void index(const string &docDirPath, const string &indexPath);

void searchBool(const string &indexPath, const string &qStr);
void searchBool(const string &indexPath, istream &in);

void searchPhrase(const string &indexPath, const string &qStr);
void searchPhrase(const string &indexPath, istream &in);

}
#endif
