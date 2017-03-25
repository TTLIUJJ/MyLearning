#include <iostream>
#include "unp.h"
using namespace std;

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in cliaddr, servaddr;
	socklen_t len;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	for( ; ; ){
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *)&cliaddr, &len);
		if(fork() == 0){
			close(listenfd);
			cout << "In Child Process" << endl;
			exit(0);
		}
		close(connfd);
	}
	return 0;
}
