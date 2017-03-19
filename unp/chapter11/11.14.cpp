#include <iostream>
#include "unp.h"
using namespace std;

int unp_client(const char *, const char *, SA **, socklen_t*);

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	socklen_t salen;
	struct sockaddr *sa;
	
	if(argc != 3){
		cerr << "usage: daytimeudpcli <hostname/IPaddress> <service/port#>" << endl;
		return -1;
	}	
	sockfd = unp_client(argv[1], argv[2], (SA **)&sa, &salen);

	cout << "sending to ???" << endl;

	sendto(sockfd, "", 1, 0, sa, salen);

	n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
	
	recvline[n] = 0;
	fputs(recvline, stdout);

	exit(0);
}

int unp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenp)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0){
		cerr << "unp_client error for " << host << ", " << serv << ": " << gai_strerror(n) << endl;
		return -1;
	}
	ressave = res;

	do{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd >= 0)
			break;
	}while((res = res->ai_next) != NULL);

	*saptr = (SA *)malloc(res->ai_addrlen);
	memcpy(*saptr, res->ai_addr, res->ai_addrlen);
	*lenp = res->ai_addrlen;

	freeaddrinfo(ressave);

	return sockfd;
}
