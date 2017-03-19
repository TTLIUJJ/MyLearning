#include <iostream>
#include "unp.h"
#include <syslog.h>
#include <time.h>
using namespace std;

extern int daemon_proc;

int daemon_init(const char *, int );

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t addrlen, len;
	struct sockaddr *cliaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	if(argc < 2 || argc >3){
		cerr << "usage: ...." << endl;
		return -1;
	}
	daemon_init(argv[0], 0);

	if(argc == 2)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	if(argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);

	cliaddr = (struct sockaddr *)malloc(addrlen);
	
	for( ; ; ){
		len = addrlen;
		connfd = accept(listenfd, cliaddr, &len);
		err_msg("connection from %s", sock_ntop(cliaddr, len));

		ticks(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));

		close(connfd);
	}
}

int daemon_init(const char *pname, int facility)
{
	int i;
	pid_t pid;
	
	if((pid = fork()) < 0)
		return -1;
	else if(pid)
		_exit(0);
	
	if(setsid() < 0)
		return -1;
	signal(SIGHUP, SIG_IGN);
	
	if((pid = fork()) < 0)
		return -1;
	else if(pid)
		_exit(0);

	daemon_proc = 1;

	chdir("/");
	for(i = 0; i < MAXFD; ++i)
	       close(i);
	
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_WRONLY);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);

	return 0;	
}
