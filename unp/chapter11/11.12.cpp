#include <iostream>
#include "unp.h"
using namespace std;

int tcp_connect(const char *, const char *);

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	socklen_t len;
	struct sockaddr_storage ss;	//新的套接字通用结构
	
	if(argc != 3){
		cerr << "usage: daytimetcpcli <hostname/IPaddress> <service/port#>" << endl;
		return -1;
	}
	sockfd = tcp_connect(argv[1], argv[2]);
	
	len = sizeof(ss);
	getpeername(sockfd, (SA *)&ss, &len);
	char strptr[MAXLINE];
	cout << "connected to " << inet_ntop(ss.ss_family, ((struct sockaddr_in *)&ss)->sin_addr, strptr, MAXLINE) << endl;

	while((n = read(sockfd, recvline, MAXLINE)) > 0){
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
	return 0;
}


int tcp_connect(const char *host, const char *serv)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0){
		cerr << "tcp_connect error for " << host << ", " << serv << ": " << gai_strerror(n) << endl;
		return -1;
	}

	ressave = res;
	
	do{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0)
			continue;
		if(connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;		//success

		close(sockfd);
	}while((res = res->ai_next) != NULL);

	if(res == NULL){
		cerr << "tcp_connect error for " << host << ", " << serv << endl;
		return -1;
	}
	freeaddrinfo(ressave);

	return sockfd;
}

