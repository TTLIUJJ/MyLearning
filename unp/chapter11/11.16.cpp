#include <iostream>
#include "unp.h"
using namespace std;

int udp_server(const char *, const char *serv, socklen_t *);

int main(int argc, char **argv)
{
	int sockfd;
	ssize_t n;
	char buff[MAXLINE];
	socklen_t len;
	time_t ticks;
	struct sockaddr_storage cliaddr;

	if(argc == 2)
		sockfd = udp_server(NULL, argv[2], NULL);
	else if(argc == 3)
		sockfd = udp_server(argv[1], argv[2], NULL);
	else{
		cerr << "usage: daytimeudpserv error" << endl;
		return -1;
	}

	for( ; ; ){
		len = sizeof(cliaddr);
		n = recvfrom(sockfd, buff, MAXLINE, 0, (SA *)&cliaddr, &len);
		
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		sendto(sockfd, buff, strlen(buff), 0, (SA *)&cliaddr, len);
	}
	return 0;
}

int udp_server(const char *host, const char *serv, socklen_t *addrlenp)
{
	int sockfd, n;
	struct addrinfo, hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;	//这样就可以不输入主机名字
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0){
		cerr << "unp_server error " << host << ", " << serv << ": " << gai_strerror(n) << endl;
		return -1;
	}

	do{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0)
			continue;
		if(bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;

		close(sockfd);
	}while((res = res->ai_next) != NULL);

	if(res == NULL){
		cerr << "unp_server error for " << host << ", " << serv << endl;
		return -1;
	}

	if(addrlenp){
		*addrlenp = res->ai_addrlen;
	}
	freeaddrinfo(ressave);

	return sockfd;
}

