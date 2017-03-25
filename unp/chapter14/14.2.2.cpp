#include <iostream>
#include "unp.h"
using namespace std;

static void sig_alrm(int);
void dg_cli(FILE *, int, const SA *, socklen_t);

int main(int argc, char **argv)
{
	if(argc != 2){
		cerr << "IPaddress" << endl;
		return -1;
	}
	int sockfd;
	sockaddr_in servaddr;
	socklen_t len;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	len = sizeof(servaddr);
	dg_cli(stdin, sockfd, (SA *)&servaddr, len);

	return 0;
}
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t len)
{
	int n;
	char send[MAXLINE], recv[MAXLINE];

	signal(SIGALRM, sig_alrm);

	while(fgets(send, MAXLINE, fp) != NULL){
		sendto(sockfd, send, strlen(send), 0, pservaddr, len);

		alarm(5);
		cout << "timing start" << endl;
		if((n = recvfrom(sockfd, recv, MAXLINE, 0, NULL, NULL)) < 0) {
			if(errno == EINTR)
				continue;
			else
				return ;
		}
		else{
			alarm(0);
			recv[n] = 0;
			fputs(recv, stdout);
		}
	}
}

static void sig_alrm(int signo)
{
	cout << "OK, time finished" << endl;
	return ;
}
