#include <iostream>
#include <sys/time.h>
using namespace std;


int run(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	struct timeval t_start, t_finish;
	gettimeofday(&t_start, NULL);
	int res = run(argc, argv);
	gettimeofday(&t_finish, NULL);
	cout << "===========================" << endl;
	double interval = t_finish.tv_sec - t_start.tv_sec +
		double(t_finish.tv_usec - t_start.tv_usec) / 1000000;
	cout << "Time Consumed: " << interval << "s" << endl;
	return res;
}


