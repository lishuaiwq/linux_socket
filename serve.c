#include"head.h"
#define SERVE_IP "192.168.240.129"
#define SERVE_PORT 9526

int main()
{
	struct sockaddr_in addr,c_addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(SERVE_PORT); 
	inet_pton(AF_INET,SERVE_IP,(void *)&addr.sin_addr.s_addr);
    int sfd=Socket(AF_INET,SOCK_STREAM,0);//    
    Bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	listen(sfd,10);
	socklen_t len=0;
	int cfd=Accept(sfd,(struct sockaddr*)&c_addr,&len);
	char c_ip[32]={0};  
	inet_ntop(AF_INET,(void*)&c_addr.sin_addr.s_addr,c_ip,sizeof(c_ip));
	printf("client ip=%s   prot=%d\n",c_ip,ntohs(c_addr.sin_port)); 
	char buff[]="hello linux\n"; 
	while(1)
	{
	    int i=0;		
		char buf[BUFSIZ]; 
		printf("client:");
		fflush(stdout); 		
	    int n=read(cfd,buf,sizeof(buf));
	    if(n==0)
		{
		exit(-1); 
		} 
		write(STDOUT_FILENO,buf,n);
		for(;i<n;i++)
				buf[i]=toupper(buf[i]);  
	    write(cfd,buf,n); 
	} 
	close(sfd);
   close(cfd); 
} 
