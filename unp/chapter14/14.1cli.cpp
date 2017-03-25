#include <iostream>
#include "unp.h"
using namespace std;

static void connect_alarm(int);
int connect_timeo(int, const SA *, socklen_t, int);

int main(int argc, char **argv)
{
	if(argc != 2){
		cerr << "Usage: client <IPaddress>" << endl;
		return -1;
	}
	int sockfd;
	struct sockaddr_in servaddr;
	socklen_t len;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	int nesc = 10;
	len = sizeof(servaddr);
	connect_timeo(sockfd, (SA *)&servaddr, len, 10);
	
	cout << "connect_time was blocked" << endl;
	return 0;
}

int connect_timeo(int sockfd, const SA *pservaddr, socklen_t len, int nsec)
{
	int n;
	
	signal(SIGALRM, connect_alarm);
	if(alarm(nsec) != 0){
		cerr << "alarm already set" << endl;
		return -1;
	}
	if((n = connect(sockfd, pservaddr, len)) < 0){
		close(sockfd);
		if(errno == EINTR)
			errno = ETIMEDOUT;
	}
	alarm(0);

	return n;
}

static void connect_alarm(int signo)
{
	cout << "in connect_alarm" << endl;
	return ;
}
