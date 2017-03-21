#include <iostream>
#include "unp.h"
using namespace std;

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;

	if(argc != 2){
		cerr << "usage: a.out <pathname>" << endl;
		return -1;
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cerr << "socket error: " << strerror(errno) << endl;
		return -1;
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		cerr << "inet_pton error" << endl;
		return -1;
	}
	if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0){
		cerr << "connet error" << endl;
		return -1;
	}
	
	struct sockaddr_in addr;
	socklen_t addrlen;
	getsockname(sockfd, (SA *)&addr, &addrlen);
	char ptr[MAXLINE];
	char ptr2[MAXLINE];
	cout << inet_ntop(AF_INET, &addr.sin_addr, ptr, MAXLINE) << endl;
	cout << inet_ntop(AF_INET, &addr.sin_port, ptr2, MAXLINE) << endl;
	cout << addr.sin_port << endl;

	int cnt = 0;
	while((n = read(sockfd, recvline, MAXLINE)) > 0){
		++cnt;
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF){
			cerr << "fputs error" << endl;
			return -1;
		}
		if(n < 0){
			cerr << "read error" << endl;
			return -1;
		}
	}
	cout << "cnt = " << cnt << endl;
	exit(0);
}
