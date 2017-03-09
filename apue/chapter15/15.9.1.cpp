#include <iostream>
#include <sys/shm.h>
#include "apue.h"
using namespace std;

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600

char array[ARRAY_SIZE];

int main()
{
	int shmid;
	char *ptr, *shmptr;

	cout << "array[] from " << static_cast<void *>(&array[0]) 
		<< " to " << static_cast<void *>(&array[ARRAY_SIZE]) << endl;
	cout << "stack arround " << static_cast<void *>(&shmid) << endl;

	if((ptr = (char *)malloc(MALLOC_SIZE)) == NULL){
		cerr << "malloc() error" << endl;
		return -1;	
	}
	cout << "malloced from " << static_cast<void *>(ptr) 
		<< " to " << static_cast<void *>(ptr+MALLOC_SIZE) << endl;

	if((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0){
		cerr << "shmget() error" << endl;
		return -1;
	}
	char *pnull;
	if((shmptr = shmat(shmid, pnull, 0)) == -1){
		cerr << "shmat() error" << endl;
		return -1;
	}
	cout << "shared memory attach from " << static_cast<void *>(shmptr)
		<< " to " << static_cast<void *>(shmptr + SHM_SIZE) << endl;
	if(shmctl(shmid, IPC_RMID, 0) < 0){
		cerr << "shmctl() error" << endl;
		return -1;
	}

	return 0;
}	
