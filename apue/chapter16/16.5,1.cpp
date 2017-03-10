#include <iostream>
#include "apue.h"
#include <netdb.h>
#include <sys/socket.h>
using namespace std;

#define BUFLEN 128

extern int connect_retry(int, int, const struct sockaddr *, socklen_t);

void print_uptime(int sockfd)
{
	int n;
	char buf[BUFLEN];

	while((n = recv(sockfd, buf, BUFLEN, 0)) > 0)
		write(STDOUT_FILENO, buf, n)
	if(n < 0){
		cerr << "reev() error" << endl;
		return;
	}
}

int main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addinfo hint;
	int sockfd, err;

	if(argc != 2){
		cerr << "usage: ruptime error" << endl;
		return -1;	
	}
	memset(&hint, 0, sizeof(hint));
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_cannoname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

	if((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0){
		cerr << "getaddrinfo() error: " << gai_strerror(err);
		return -1;
	}
	for(aip = ailist; aip != NULL; aip = aip->ai_next){
		if((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0, aip->ai_addr, 
						aip->ai_addrlen)) < 0){
			err = errno;
		}
		else{
			print_uptime(sockfd);
			exit(0);
		}
	}
	cerr << err << " can't connetc to " << agrv[1] << endl;
}
