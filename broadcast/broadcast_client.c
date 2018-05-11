#include"head.h"

#define CLIENT_PROT 9526
//#define CLIENT_IP "192.168.240.130"
int main()
{
 int fd=Socket(AF_INET,SOCK_DGRAM,0); 
 struct sockaddr_in client;
 char buf[1024]={0};  
 client.sin_family=AF_INET;
 client.sin_port=htons(CLIENT_PROT);
inet_pton(AF_INET,"0.0.0.0",&client.sin_addr.s_addr); 
//client.sin_addr.s_addr=htonl(INADDR_ANY); 
Bind(fd,(struct sockaddr*)&client,sizeof(client));
 printf("bing success\n"); 
 while(1)
 {
		 printf("recvfrom:");
		 fflush(stdout); 
    int n=recvfrom(fd,buf,sizeof(buf),0,NULL,0);
	if(n<0)
		{
		  perror("use recv");
		  exit(1); 
		} 
//	printf("%s\n",buf); 
	write(STDOUT_FILENO,buf,n);
	fflush(stdout); 
 } 
 close(fd); 
   return 0;
}  
