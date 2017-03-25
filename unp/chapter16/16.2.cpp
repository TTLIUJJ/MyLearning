//version--noblocking, client
#include <iostream>
#include <time.h>
#include "unp.h"
using namespace std;

void str_cli(FILE *, int);
char *gf_time();

int main(int argc, char **argv)
{
	if(argc != 2){
		cerr << "Usage: error <IPaddress>" << endl;
		return -1;
	}
	int sockfd;
	struct sockaddr_in servaddr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(50000);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);
	close(sockfd);

	return 0;
}

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1, val, stdineof;
	int n, nwritten;
	fd_set rset, wset;
	char to[MAXLINE], fr[MAXLINE];
	char *toiptr, *tooptr, *friptr, *froptr;

	val = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

	val = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);

	val = fcntl(STDOUT_FILENO, F_GETFL, 0);
	fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);
	
	toiptr = tooptr = to;
	friptr = froptr = fr;
	stdineof = 0;
	
	maxfdp1 = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;
	for( ; ; ){
		FD_ZERO(&rset);
		FD_ZERO(&wset);
		
		if(stdineof == 0 && toiptr < &to[MAXLINE])
			FD_SET(STDIN_FILENO, &rset);
		if(friptr < &fr[MAXLINE])
			FD_SET(sockfd, &rset);
		if(tooptr != toiptr)
			FD_SET(sockfd, &wset);
		if(froptr != friptr)
			FD_SET(STDOUT_FILENO, &wset);
		
		select(maxfdp1, &rset, &wset, NULL, NULL);
		
		if(FD_ISSET(STDIN_FILENO, &rset)){
			if((n = read(STDIN_FILENO, toiptr, &to[MAXLINE] - toiptr)) < 0){
				if(errno != EWOULDBLOCK){
					cerr << "read error on stdin" << endl;
					return ;
				}
			}
			else if(n == 0){
				fprintf(stderr, "%s: EOF on stdin\n", gf_time());
				stdineof = 1;
				if(toiptr == tooptr)
					shutdown(sockfd, SHUT_WR);
			}
			else{
				fprintf(stderr, "%s: read %d bytes from stdin\n", gf_time(), n);
				toiptr += n;
				FD_SET(sockfd, &wset);
			}
		}
		if(FD_ISSET(sockfd, &rset)){
			if((n = read(sockfd, friptr, &fr[MAXLINE] - friptr)) < 0){
				if(errno != EWOULDBLOCK){
					cerr << "read error on sockfd" << endl;
					return ;
				}
			}
			else if(n == 0){
				fprintf(stderr, "%s: EOF on socket\n", gf_time());
				if(stdineof)
					return;
				else{
					cerr << "str_cli: server terminated prematurely" << endl;
					return;
				}
			}
			else{
				fprintf(stderr, "%s: read %d btyes from socket\n", gf_time(), n);
				friptr += n;
				FD_SET(STDOUT_FILENO, &wset);
			}
		}
		if(FD_ISSET(STDOUT_FILENO, &wset) && (n = friptr - froptr) > 0){
			if((nwritten = write(STDOUT_FILENO, froptr, n)) < 0){
				if(errno != EWOULDBLOCK){
					cerr << "write error to stdout" << endl;
					return ;
				}
			}
			else{
				fprintf(stderr, "%s: worte %d btyes to stdout\n", gf_time(), nwritten);
				froptr += nwritten;
				if(froptr == friptr)
					froptr = friptr = fr;
			}
		}
		if(FD_ISSET(sockfd, &wset) && (n = toiptr - tooptr) > 0){
			if((nwritten = write(sockfd, tooptr, n)) < 0){
				if(errno != EWOULDBLOCK){
					cerr << "write error to sockfd" << endl;
					return;
				}
			}
			else{
				fprintf(stderr, "%s: wrote %d bytes to socket\n", gf_time(), nwritten);
				tooptr += nwritten;
				if(tooptr == toiptr){
					tooptr = toiptr = to;
					if(stdineof)
						shutdown(sockfd, SHUT_WR);
				}
			}
		}
	}
}

char *gf_time()
{
	struct timeval tv;
	static char str[30];
	char *ptr;

	if(gettimeofday(&tv, NULL) < 0){
		cerr << "gettimeofday error" << endl;
	}

	ptr = ctime(&tv.tv_sec);
	strcpy(str, &ptr[11]);

	snprintf(str + 8, sizeof(str) - 8, ".%06ld", tv.tv_usec);

	return str;
}
