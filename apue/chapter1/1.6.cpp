#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	cout<<"hello world from process ID"<<static_cast<long>(getpid())<<endl;
	return 0;
}
