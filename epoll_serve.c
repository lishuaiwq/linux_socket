#include"head.h"

#define SERVE_IP "192.168.240.130"

#define PROT 9526
int main()
{
	struct sockaddr_in serve,client;	
    int listenfd=Socket(AF_INET,SOCK_STREAM,0);
	serve.sin_family=AF_INET;
	serve.sin_port=htons(PROT);
	inet_pton(AF_INET,SERVE_IP,(void*)&serve.sin_addr.s_addr);
	Bind(listenfd,(struct sockaddr*)&serve,sizeof(serve));   
	Listen(listenfd,20);
    int epollfd=epoll_create(10); 
	struct epoll_event tep,even[10];
	tep.events=EPOLLIN;
	tep.data.fd=listenfd;
	int ep=epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&tep); 
  
	while(1)
	{
		int i=0; 	
	   int size=epoll_wait(epollfd,even,10,0);  	
       	if(size==-1)
		{
		  perror("use epoll_wait");
		  exit(1); 
		} 
		for(i=0;i<size;i++)
		{
		    if(!(even[i].events&EPOLLIN))
			     continue;
			if(even[i].data.fd==listenfd) 
			{		
			socklen_t len=sizeof(client); 		
			int confd=Accept(listenfd,(struct sockaddr*)&client,&len); 
			char buf[20]={0};   
    printf("IP=%s   prot=%d\n",inet_ntop(AF_INET,(void*)&client.sin_addr.s_addr,buf,sizeof(buf)),ntohs(client.sin_port)); 
	       
	tep.events=EPOLLIN;
	tep.data.fd=confd;
	int ep=epoll_ctl(epollfd,EPOLL_CTL_ADD,confd,&tep);
	if(ep==-1)
	{
	  perror("use epoll_ctl");
	  exit(1); 
	} 
			} 
			else
			{
				char buf[1024]={0}; 	 
		          int sockfd=even[i].data.fd;
				  int n=read(sockfd,buf,sizeof(buf));
				  if(n<0)
				  {
				     perror("use read");
					 epoll_ctl(epollfd,EPOLL_CTL_DEL,sockfd,NULL);
					 close(sockfd); 
				  } 
				  else if(n==0)
				  {
				       
					 epoll_ctl(epollfd,EPOLL_CTL_DEL,sockfd,NULL);
					 close(sockfd); 
				  }
				  else
				  {
				      printf("client:%s",buf);
					  for(i=0;i<n;i++)
							  buf[i]=toupper(buf[i]);
					  write(sockfd,buf,n); 
				  } 
			} 
		} 

	} 
  return 0;
} 
