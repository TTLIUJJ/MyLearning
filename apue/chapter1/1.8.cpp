#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	cout<<"uid = " << getuid()<<" gid = "<<getgid()<<endl; 
	return 0;
}
