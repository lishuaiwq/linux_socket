#include"head.h"

#define SERVE_IP "192.168.240.130"
#define PROT 9526 
int main()
{
	int listenfd;	
    struct sockaddr_in serve,clien;
    struct pollfd client[1024];
    listenfd=Socket(AF_INET,SOCK_STREAM,0);
    serve.sin_family=AF_INET;
	serve.sin_port=htons(PROT);
	inet_pton(AF_INET,SERVE_IP,(void *)&serve.sin_addr.s_addr); 

	bzero(&clien,sizeof(clien)); 
	Bind(listenfd,(struct sockaddr* )&serve,sizeof(serve)); 

	Listen(listenfd,20);
	int j;
    
	client[0].fd=listenfd; 
    client[0].events=POLLRDNORM;
	//cleint[0].revents=0;

    for(j=1;j<1024;j++)
			client[j].fd=-1; 
	int maxi=0;
	int nready;
	char dest[1024]={0};  
	int i;
  while(1) 	  
  {
		 nready=poll(client,maxi+1,-1); 
		 if(nready==-1)
		 {
		     perror("poll");
			 exit(-1); 
		 } 
		if(client[0].revents&POLLRDNORM)
		{
			socklen_t len=sizeof(clien);	
		   int connfd=Accept(listenfd,(struct sockaddr*)&clien,&len);
		   printf("client ip=%s    prot=%d\n",inet_ntop(AF_INET,(void *)&clien.sin_addr.s_addr,dest,sizeof(clien)),ntohs(clien.sin_port));

       	for(i=1;i<1024;i++)
		{
		     if(client[i].fd<0)
			 {
			    client[i].fd=connfd;
                client[i].events=POLLRDNORM;
				break;
			 } 
		} 
		if(maxi<i)
		  maxi=i;
		if(--nready<=0)
		   continue;
		}
	for(i=1;i<=maxi;i++)
	{
	    int sockfd=client[i].fd;
		if(sockfd<0)
	      continue;
       if(client[i].revents==POLLRDNORM | POLLERR)
	   {
		   char buf[1024]; 	   
	       int n=read(sockfd,buf,sizeof(buf));
		   if(n<0)
		   {
		      if(errno==ECONNRESET)
			  {
			     close(sockfd);
				 client[i].fd=-1;
			  } 
			  else
			  {
			      perror("exit"); 
			  } 
		   } else if(n==0)
		   {
		      exit(-1); 
		   } else
		   {
				  int i; 
		          printf("client:");
				  fflush(stdout); 
				  write(STDOUT_FILENO,buf,n); 
                for(i=0;i<n;i++)
						buf[i]=toupper(buf[i]);
				write(sockfd,buf,n); 
		   }
		   if(--nready<=0)
		     {
		      break;
		   } 
	   }
	} 
  }
   return 0;
} 
