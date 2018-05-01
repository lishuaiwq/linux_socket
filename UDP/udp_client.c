#include"head.h"
#define PROT 9526
int main()
{
  struct sockaddr_in client;	
  char buf[1024]={0};  
  int listenfd= Socket(AF_INET,SOCK_DGRAM,0);
  client.sin_family=AF_INET;
  client.sin_port=htons(PROT);
  inet_pton(AF_INET,"192.168.240.130",&client.sin_addr.s_addr); 
  while(1)
  {
     int nn=read(STDIN_FILENO,buf,sizeof(buf)); 
	 if(nn<0)
	 {
	    perror("use read");
		exit(1); 
	 } else if(nn==0)
	 {	 
	    exit(2); 
	 }
	 else
	 {
	    int s=sendto(listenfd,buf,nn,0,(struct sockaddr*)&client,sizeof(client)); 
		if(s<0)
		{
		  perror("use sendto");
		  exit(3); 
		} 
	 } 
     int n=recvfrom(listenfd,buf,sizeof(buf),0,NULL,0);
	 if(n<0)
	 {
	    perror("use recvfrom");
		exit(3); 
	 } 
	 write(STDOUT_FILENO,buf,n); 
  } 
  close(listenfd);
  return 0;
} 
