#include <iostream>
#include "unp.h"
using namespace std;

void str_cli(int);

int main(int argc, char **argv)
{
	if(argc != 2){
		cerr << "Usage: <IPaddress>" << endl;
		return -1;
	}
	int sockfd;
	struct sockaddr_in servaddr;

	socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
	str_cli(sockfd);
	
	close(sockfd);

	return 0;
}

void str_cli(int sockfd)
{
	pid_t pid;
	char send[MAXLINE], recv[MAXLINE];

	if((pid = fork()) == 0){
		while(read(sockfd, recv, MAXLINE) > 0)
			write(STDOUT_FILENO, recv, strlen(recv));

		kill(getppid(), SIGTERM);
		exit(0);
	}
	while(read(STDIN_FILENO, send, MAXLINE) > 0)
		write(sockfd, send, strlen(send));
	
	shutdown(sockfd, SHUT_WR);
	pause();

	return;
}
