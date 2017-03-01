#include <iostream>
#include "apue.h"
using namespace std;
int main()
{
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;
	cout << tmpnam(NULL) << endl;
	tmpnam(name);
	cout << name << endl;

	if((fp = tmpfile()) == NULL){
		cerr << "Tempfile Error" << endl;
		return -1;
	}
	fputs("one lien of output\n", fp);
	rewind(fp);
	if(fgets(line, sizeof(line), fp) == NULL){
		cerr << "Fgets() Error" << endl;
		return -1;
	}
	fputs(line, stdout);

	return 0;
}
