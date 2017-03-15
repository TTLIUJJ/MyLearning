#include <iostream>
#include "unp.h"
using namespace std;

void str_cli(FILE *, int);

int main(int argc, char **argv)
{
	int i, sockfd[5];
	struct sockaddr_in servaddr;
	
	if(argc != 2){
		cerr << "usage: tcpcli<IPaddress>" << endl;
		return -1;
	}
	for(i = 0; i < 5; ++ i){
		sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
		
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

		connect(sockfd[i], (SA *)&servaddr, sizeof(servaddr));
	}
	str_cli(stdin, sockfd[i]);
	
	exit(0);
}

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	
	while(fgets(sendline, MAXLINE, fp) != NULL){
		write(sockfd, sendline, strlen(sendline));

		if(read(sockfd, recvline, MAXLINE) == 0){
			cerr << "read error" << endl;
			exit(0);
		}
		fputs(recvline, stdout);
	}
}
