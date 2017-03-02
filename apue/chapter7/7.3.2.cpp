#include <iostream>
#include "apue.h"
using namespace std;
static void my_exit1();
static void my_exit2();
static void my_exit3();
int main()
{
	if(atexit(my_exit2) != 0){
		cout << "Can't register my_exit2" << endl;
		return -1;
	}
	if(atexit(my_exit1) != 0){
		cout << "Can't register my_exit2" << endl;
   		return -1;
	}
        if(atexit(my_exit3) != 0){
		cout << "Can't register my_exit2" << endl;
		 return -1;				
	}
        if(atexit(my_exit1) != 0){
    		cout << "Can't register my_exit2" << endl;
		return -1;	
	}
	cout << "Main Done" << endl;

}
static void my_exit1()
{
	cout << "First exit handler" << endl;
}
static void my_exit2()
{
	cout << "Second exit handler" << endl;
}
static void my_exit3()
{
	cout << "Third exit handler" << endl;
}
