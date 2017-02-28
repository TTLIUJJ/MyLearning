#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	if(chdir("/temp") < 0){
		cerr << "Chdir error" << endl;
		return -1;
	}
	cout << "Chdir to /4.23.cpp succeeded" << endl;

	return 0;
}
