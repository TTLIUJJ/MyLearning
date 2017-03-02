#include <iostream>
#include <shadow.h>
#include "apue.h"
using namespace std;
int main()
{
	struct spwd *ptr;
	if((ptr = getspnam("ttlj@ttlj-Lenovo-M495")) == NULL){
		cerr << "Getspnam Error" << endl;
		return -1;
	}
	printf("sp_pwdp = %s\n", ptr->sp_pwdp == NULL || ptr->sp_pwdp[0] == 0 ?
		"(null)" : ptr->sp_pwdp);
	
	return 0;
}
