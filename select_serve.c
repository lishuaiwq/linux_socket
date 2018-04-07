#include"head.h"

#define SERVE_IP "192.168.240.129"
#define PROT 9526
int main()
{
	int listenfd;
	struct sockaddr_in serve,clien;
    listenfd=Socket(AF_INET,SOCK_STREAM,0);
	serve.sin_family=AF_INET;
	serve.sin_port=htons(PROT);
	inet_pton(AF_INET,SERVE_IP,(void*)&serve.sin_addr.s_addr); 
    Bind(listenfd,(struct sockaddr*)&serve,sizeof(serve));
    Listen(listenfd,20);
    
	int i,max,maxi,client[1024],nready,confd;
	fd_set allset,reset;
	max=listenfd;
	maxi=-1;
	for(i=0;i<1024;i++)
		client[i]=-1;
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset); 
    while(1)
	{
	  reset=allset;
      nready=select(max+1,&reset,NULL,NULL,NULL); 
	  if(nready<0)
	  {
	     perror("select");
		 exit(-1); 
	  } 
     if(FD_ISSET(listenfd,&reset))
	 {
			 socklen_t  socklen=sizeof(clien);
			 char src[40]={0};  
	        confd=Accept(listenfd,(struct sockaddr*)&clien,&socklen); 
			printf("client ip=%s    prot=%d\n",inet_ntop(AF_INET,(void*)&clien.sin_addr.s_addr,src,sizeof(src)),ntohs(clien.sin_port)); 
           for( i=0;i<1024;i++)
		   {
		       if(client[i]<0)
			   {
					   client[i]=confd;
					   break;
			   }
		   } 
           if(i==1024)
		   {
		     printf("too many client\n");
			 exit(-1); 
		   } 
         FD_SET(confd,&allset);

		 if(confd>max)
				 max=confd;
		 if(i>maxi)
				maxi=i;
		 if(--nready==0)
				 continue;
	 } 
	 for(i=0;i<=maxi;i++)
	 {
		int sockfd;	 
	    if((sockfd=client[i])<0)
		   continue;
		if(FD_ISSET(sockfd,&reset))
		{
			int n;	
			char buf[1024]={0};  
		  n=read(sockfd,buf,sizeof(buf));
		  if(n==0) 
		  {
				close(sockfd);  
		      FD_CLR(sockfd,&allset); 
			  client[i]=-1; 		  
		  } 
		  else
		  {
			 printf("client:%s",buf); 	  
		     int i=0;
			 for(;i<n;i++)
					 buf[i]=toupper(buf[i]);
			 write(sockfd,buf,n); 
		  } 
		if(--nready==0)
				break;
		} 
	 }
	} 
	close(listenfd); 
	return 0;
} 		
