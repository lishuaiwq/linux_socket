#include"head.h"

#define CLIENT_IP "192.168.240.129"
#define CLIENT_PROT 9526
int main()
{
	 struct sockaddr_in caddr;
	 caddr.sin_family=AF_INET;
	 caddr.sin_port=htons(CLIENT_PROT); 
	 inet_pton(AF_INET,CLIENT_IP,(void*)&caddr.sin_addr.s_addr);
     int cfd=Socket(AF_INET,SOCK_STREAM,0);
     Connect(cfd,(void*)&caddr,sizeof(caddr));  
     while(1)
	 {
		char buf[1024]={0};  	 
		printf("client:");
		fflush(stdout); 		
	    int n=read(STDIN_FILENO,buf,sizeof(buf)); 
		 write(cfd,buf,n);
		read(cfd,buf,sizeof(buf));
        printf("serve:%s",buf); 
	 } 
} 
