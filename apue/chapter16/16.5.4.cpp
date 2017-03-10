#include <iostream>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include "apue.h"
using namespace std;

#define BUFLEN 128
#define TIMEOUT 20

void sigalrm(int signo)
{

}

void print_uptime(int sockfd, struct addrinfo *aip)
{
	int n;
	char buf[BUFLEN];

	buf[0] = 0;
	if(sendto(sockfd, buf, 1, 0, aip->ai_addr, aip->ai_addrlen) < 0){
		cerr << "sendto() error" << endl;
		return -1;
	}
	alarm(TIMEOUT);
	if((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0){
		if(errno != EINTR)
			alarm(0);
		cerr << "recvfrom error" << endl;
		return -1;
	}
	alarm(0);
	write(STDOUT_FILENO, buf, n);
}

int main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int sockfd, err;
	struct sigaction sa;

	if(argc != 2){
		cerr << "usage: ruptime hostname" << endl;
		return -1;
	}
	sa.sa_handler = sigalrm;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if(sigaction(SIGALRM, &sa, NULL) < 0){
		cerr << "sigaction() error" << endl;
		return -1;
	}
	memset(&hint, 0, sizeof(hint));
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_cononname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0){
		cerr << "getaddrinfo error: " << gai_strerror(err);
	       	return -1;
	}
	for(aip = ailist; aip != NULL; aip = aip->ailist){
		if((sockfd = socket(aip->ai_family, SOCK_DGRAM, 0)) < 0)
			err = errno;
		else{
			printf_uptime(sockfd, aip);
			exit(0);
		}
	}
	exit(1);
}
