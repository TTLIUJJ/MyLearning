#include <iostream>
#include <string>
#include "unp.h"
using namespace std;

int _error(const string &s);

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in6 servaddr;

	if(argc != 2)
		_error("usage: a.out <IPaddresss>");
	if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
		_error("socket error");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(13);
	if(inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
		_error("inet_pton error");
	if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		_error("connet error");
	while((n = read(sockfd, recvline, MAXLINE)) > 0){
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF)
			_error("fputs error");
	}
	if(n < 0)
		_error("read error");
	exit(0);
}

int _error(const string &s)
{
	cerr << s << endl;
	return -1;
}
