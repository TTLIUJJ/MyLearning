#include <iostream>
#include "apue.h"
using namespace std;

void print_family(struct addinfo *aip)
{
	cout << " family: ";
	switch(aip->ai_family){
		case AF_INENT: cout << "AF_INENT"; break;
		case AF_INET6: cout << "AF_INET6"; break;
		case AF_UNIX:  cout << "AF_UNIX" ; break;
		case AF_UNSPEC:cout << "AF_UNSPEC";break;
		default:
			cout << "UNKNOWN";
	}
}

void print_type(struct addinfo *aip)
{
	cout << " type: ";
	switch(aip->ai_socktype){
		case SOCK_SEQPACKET: cout << "SOCK_SEQPACKET"; break;
		case SOCK_STREAM:    cout << "SOCK_STREAM";    break;
		case SOCK_DGRAM:     cout << "SOCK_DGRAM";     break;
		case SOCK_RAW:       cout << "SOCK_RAW";       break;
		default:
			cout << "UNKNOWN-" << aip->ai_socktype;
	}
}

void print_protocol(struct addinfo *aip)
{
	cout << " protocol: ";
	switch(aip->protocol){
		case 0: 	  cout << "DEFAULT"; break;
		case IPPROTO_TCP: cout << "TCP"    ; break;
		case IPPROTO_UDP: cout << "UDP"    ; break;
		case IPPROTO_RAW: cout << "RAW"    ; break;
		default:
			cout << "UNKNOWN-"<< aip->ai_protocol;
	}
}

void print_flags(struct addinfo *aip)
{
	cout << " flags: ";
	if(aip->ai_flags == 0)
		cout << "0";
	else{
		if(aip->ai_flags & AI_ALL)
			cout << "AI_ALL";
		if(aip->ai_flags & AI_CANONNAME)
			cout << "AI_CANONNAME";
		if(aip->ai_flags & AI_NUMERICHOST)
			cout << "AI_UNMERICHOST";
		if(aip->ai_flags & AI_NUMERICSERV)
			cout << "AI_NUMERICSERV";
		if(aip->ai_flags & AI_PASSIVE)
			cout << "AI_NUMRICSERV";
		if(aip->ai_flags & AI_V4MAPPED)
			cout << "AI_V4MAPPED";
	}
}

int main(int argc, char *argv[])
{
	
}
