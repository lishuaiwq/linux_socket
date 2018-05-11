#include"head.h"

#define CLIENT_PROT 9526 
//#define SERVE_PROT   8888

#define CLIENT_IP "192.168.3.255"
int main()
{
  int fd=Socket(AF_INET,SOCK_DGRAM,0);
   

  struct sockaddr_in serve,client;
  client.sin_family=AF_INET;
  client.sin_port=htons(CLIENT_PROT);
  inet_pton(AF_INET,CLIENT_IP,&client.sin_addr.s_addr);
  
 
//  serve.sin_family=AF_INET;
 // serve.sin_port=htons(SERVE_PROT);
 // serve.sin_addr.s_addr=htonl(INADDR_ANY);
  
// Bind(fd,(struct sockaddr*)&serve,sizeof(serve)); 


  int flag=1;
  setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag)); 
  int i=0;
  char buf[1024]={0};  
  while(1)
  {
	strcpy(buf,"天王盖地虎、宝塔镇河妖\n");
	printf("serve:%s",buf); 
    int s=sendto(fd,buf,strlen(buf),0,(struct sockaddr*)&client,sizeof(client)); 
	if(s<0)
	{
	   perror("use sendto");
	   exit(-1); 
	} 
	sleep(1); 
  } 
  close(fd); 
   return 0;
} 
