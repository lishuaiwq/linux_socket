#include<stdio.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<stdlib.h>
int main()
{
  int fd[2]; 		
  pid_t pid;
  char buf[]="AAAA\nBBBB\n"; 	  
  int sum=sizeof(buf);
  int p=pipe(fd);
  if(p<0)
  {
     perror("use pipe");
	 exit(-1); 
  } 
  pid=fork();
  if(pid==0)
  { 
     close(fd[0]);
    while(1)
	{
	   printf("red  1\n"); 		
	   write(fd[1],buf,sizeof(buf));
	   sleep(5); 
	} 
  } else if(pid>0)
  {
       close(fd[1]);
	   char buff[1024]; 
		struct epoll_event eve,even[10];
		eve.events=EPOLLIN | EPOLLET;
		eve.data.fd=fd[0];
		int epollfd=epoll_create(10);
        epoll_ctl(epollfd,EPOLL_CTL_ADD,fd[0],&eve);    
	   while(1)
	   {
	       int n=epoll_wait(epollfd,even,10,-1);
		   if(n<0)
		   {
		      perror("use epoll");
			  exit(-1); 
		   } 
		   int nn=read(fd[0],buff,sum/2);
		   if(nn>0)
		   {
		     write(STDOUT_FILENO,buff,nn);
			 printf("_______________\n"); 
		   } else
		   {
		      perror("use read");
			  exit(-1); 
		   } 
	   } 
  } 
} 
