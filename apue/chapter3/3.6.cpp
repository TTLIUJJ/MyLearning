#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		cout<<"Cann't seek"<<endl;
	else
		cout<<"Seek Ok!"<<endl;
	return 0;
}
