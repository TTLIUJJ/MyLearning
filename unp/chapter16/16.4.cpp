#include <iostream>
#include "unp.h"
using namespace std;

int connect_nonb(int, const SA *, socklen_t, int);

int main(int argc, char **argv)
{

}

int connect_nonb(int scokfd, const SA *saptr, socklen_t salen, int nsec)
{
	int flags, n, error;
	socklen_t len;
	fd_set rset, wset;
	struct timeval, tval;

	flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	error = 0;
	if((n = connect(sockfd, saptr, salen)) < 0){
		if(error != EINPROGRESS)
			return -1;
	}

	if(n == 0)
		goto done;

	FD_SET(&rset);
	FD_SET(sockfd, &rset);
	wset = rset;
	tval.tv_sec = nsec;
	tval.tv_usec = 0;

	if((n = select(sockfd+1, &rset, &wset, NULL, NULL, nsec ? &tval : NULL)) == 0){
		close(sockfd);
		errno = ETIMEOUT;
		return -1;
	}
	if(FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)){
		len = sizeof(error);
		if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			return -1;
	}
	else{
		cerr << "select error: sockfd not set" << endl;
		return -1;
	}
done:
	fcntl(sockfd, F_SETFL, flags);

	if(error){
		close(sockfd);
		errno = error;
		return -1;
	}
	return 0;
}
