#include <iostream>
#include <fcntl.h>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	if(argc != 2){
		cerr << "Usage: a.out<pathname>"<<endl;
		return -1;
	}	
	if(access(argv[1], R_OK) < 0){
		cerr << "Acess error for " << argv[1] << endl;
	}
	else
		cout << "Read Acess Ok" << endl;
	if(open(argv[1], O_RDONLY) < 0){
		cerr << "Open error for " << argv[1] << endl;
		return -1; 
	}
	else
		cout << "Open for reading ok"<< endl;
	
	return 0;
}
