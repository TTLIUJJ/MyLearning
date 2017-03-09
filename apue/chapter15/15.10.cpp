#include <iostream>
#include "slock.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

struct slock* s_alloc()
{
	struct slock *sp;
	static int cnt;

	if((sp = malloc(sizeof(struct slock))) == NULL)
		return NULL;
	do{
		snprintf(sp->name, sizeof(sp->name), "/%ld.%d", (long)getpid(), cnt++);
		sp->semp = sem_open(sp->name, O_CREAT|O_EXCL, S_IRWXU, 1);
	}
	while((sp->semp == SEM_FAILD) && (errno == EEXIST));
	if(sp->semp == SEMFAILD){
		free(sp);
		return NULL;
	}
	sem_unlink(sp->name);
	return sp;
}
void s_free(struct slock *sp)
{
	sem_close(sp->semp);
	free(sp);
}
int s_lock(struct slock *sp)
{
	return (sem_wait(sp->name));
}

int s_trylock(struct slock *sp)
{
	return (sem_trywait(sp->name));
}
int s_unlock(struct slock *sp)
{
	return (sem_post(sp->semp));
}
