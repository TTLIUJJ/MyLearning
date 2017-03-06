#include <iostream>
#include <string>
#include <limits.h>

#define MAXSTRINGSZ 4096
static char envbuf[MAXSTRINGSZ];
extern char **environ;

char *getenv(const string &name)
{
	int i, len;
	
	len = name.size();
	for(i = 0; environ[i] != NULL; ++i){
		if(name == environ[i] && (environ[i][len] == '=')){
			strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
			return (envbuf);
		}
	}
	return NULL;
}
