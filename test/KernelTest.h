#ifndef _KERNEL_TEST_
#define _KERNEL_TEST_

#include <KernelTest.h>
#include <string>

using namespace std;


class KernelTest {
public:
	static void index(const string &docDirPath, const string &indexPath);
	static void search(const string &indexPath, const string &qStr);
};


#endif
