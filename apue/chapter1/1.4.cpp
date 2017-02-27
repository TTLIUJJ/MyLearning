#include <iostream>
#include "dirent.h"
#include <cstdlib>
#include <cstdio>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;
	if(argc != 2)
		cout<<"usage ls directory_name"<<endl;
	if((dp = opendir(argv[1]))==NULL)
		cout<<"Can't open "<<argv[1]<<endl;
	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	
	closedir(dp);
	exit(0);
}
