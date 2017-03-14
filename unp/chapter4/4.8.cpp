void serve()
{
	pid_t pid;
	socklen_t len, addrlen;
	struct sockaddr serv_addr;
	int listenfd, connfd;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bind(listenfd, (SA *)&serv_addr, sizeof(len));
	listen = (listenfd, LISTENQ);

	for( ; ; ){
		addrlen = sizeof(serv_addr);
		connfd = accept(listenfd, (SA *)&serv_addr, &addrlen);

		if((pid = fork()) == 0){
			close(listenfd);
			//doit(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);
	}

}

