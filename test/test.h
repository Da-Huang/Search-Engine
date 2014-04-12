#ifndef _TEST_H_
#define _TEST_H_

#include <string>
using namespace std;
namespace test {


void index(const string &docDirPath, const string &indexPath);
void twIndex(const string &docDirPath, const string &indexPath);
void littleIndex();

void twSearch(const string &indexPath, const string &qStr, 
		bool fuzzy=false);
void twSearch(const string &indexPath, istream &in, 
		bool fuzzy=false);

void search(const string &indexPath, const string &qStr, bool fuzzy=false);
void search(const string &indexPath, istream &in, bool fuzzy=false);

void searchBool(const string &indexPath, const string &qStr, 
		bool fuzzy=false);
void searchBool(const string &indexPath, istream &in, bool fuzzy=false);

void searchPhrase(const string &indexPath, const string &qStr, 
		bool fuzzy=false);
void searchPhrase(const string &indexPath, istream &in, bool fuzzy=false);


}
#endif
