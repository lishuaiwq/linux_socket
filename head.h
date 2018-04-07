#ifndef _HEAD_H__
#define _HEAD_H__
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include<pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
extern int errno;
int Socket(int domain,int type,int protocol);
int Bind(int sockfd,const struct sockaddr* addr,socklen_t addrlen);
int Listen(int sockfd,int backlog);
int Accept(int sockfd,struct sockaddr* addr,socklen_t* addrlen);
int Connect(int Sockfd,const struct sockaddr* addr,socklen_t addrlen);

#endif

