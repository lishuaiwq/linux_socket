#include"head.h"
#define SERVE_IP "192.168.240.129"
#define SERVE_PORT 9526

void fun(int sig)
{
    while(waitpid(0,NULL,WNOHANG)>0);
	return;
} 
int main()
{
	int number=1;	
	pid_t pid;		
	struct sockaddr_in addr,c_addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(SERVE_PORT); 
	inet_pton(AF_INET,SERVE_IP,(void *)&addr.sin_addr.s_addr);
    int sfd=Socket(AF_INET,SOCK_STREAM,0);//    
    Bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	listen(sfd,10);
	int cfd;
	while(1)
	{
	socklen_t len=0;
	cfd=Accept(sfd,(struct sockaddr*)&c_addr,&len);
	char c_ip[32]={0};  
	inet_ntop(AF_INET,(void*)&c_addr.sin_addr.s_addr,c_ip,sizeof(c_ip));
	printf("client ip=%s   prot=%d\n",c_ip,ntohs(c_addr.sin_port)); 
    pid=fork();
    if(pid==0)
	{
			close(sfd); 
			break;
	}
	else
	{
	   close(cfd);
	   signal(SIGCHLD,fun); 
	} 
  }
	if(pid==0)
    {
	     while(1)
		 {
			int i=0;	 
			char buf[1024]={0};  	
		    int n=read(cfd,buf,sizeof(buf));
            if(n==0)
			{
				sleep(10); 
				close(cfd);
				//sleep(20); 
			    exit(-1); 
			} 
             printf("%dth client:%s",number++,buf);
			 for(;i<n;i++)
					 buf[i]=toupper(buf[i]);
			 write(cfd,buf,n); 
		 } 		 
	} 			
} 
