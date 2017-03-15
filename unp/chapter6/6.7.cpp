#include <iostream>
#include "unp.h"
using namespace std;

void str_cli(FILE *, int);

int main(int argc, char **argv)
{
	int i, sockfd[5];
	struct sockaddr_in servaddr;

	if(argc != 2){
		cerr << "usage: tcpclient <IPaddress>" << endl;
		return -1;
	}

	for(i = 0; i < 5; ++i){
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
	int maxfd1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);
	for( ; ; ){
		if(stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfd1 = max(sockfd, fileno(fp)) + 1;
		select(maxfd1, &rset, NULL, NULL, NULL);
		
		if(FD_ISSET(sockfd, &rset)){
			if((n = read(sockfd, buf, MAXLINE)) == 0){
				if(stdineof == 1)
					return;
				else{
					cerr << "read error" << endl;
					return;
				}
			}
			write(fileno(stdout), buf, n);
		}

		if(FD_ISSET(fileno(fp), &rset)){
			if((n = read(fileno(fp), buf, MAXLINE)) == 0){
				stdineof = 1;
				shutdown(sockfd, SHUT_WR);	//关闭之后，不能往服务器进行写操作，但是可以进行读操作
				FD_CLR(fileno(fp), &rset);	//关闭文件描述符
				continue;			//此时可能还有数据可以读，不能跳出循环
			}
			write(sockfd, buf, n);
		}
	}
}
