#include"head.h"
//#define PROT 9527
int main(int argc,char* argv[])
{ 
  struct sockaddr_in serve,client;
  char buf[1024]={0}; 
  char buff[1024]={0};  
  int i;
  int listenfd=Socket(AF_INET,SOCK_DGRAM,0);
  serve.sin_family=AF_INET;
  serve.sin_port=htons(atoi(argv[2])); 
 // serve.sin_addr.s_addr=htonl(INADDR_ANY); 
 inet_pton(AF_INET,argv[1],(void*)&serve.sin_addr.s_addr);
  Bind(listenfd,(struct sockaddr*)&serve,sizeof(serve));
  bzero(&client,sizeof(client)); 
  while(1)
  {
	  socklen_t len=sizeof(client); 	  
      int n=recvfrom(listenfd,buf,sizeof(serve),0,(struct sockaddr*)&client,&len);
      if(n<0)
	  {
	    perror("perror recvfrom");
		exit(2); 
	  }
      printf("ip=%s    prot=%d\n",inet_ntop(AF_INET,(void*)&client.sin_addr.s_addr,(void*)&buff,\
					  \
					  sizeof(buf)),ntohs(client.sin_port)); 
	  for(i=0;i<n;i++)
			  buf[i]=toupper(buf[i]);
	  printf("client:");
	  fflush(stdout); 
	  write(STDOUT_FILENO,buf,n);

	  int s=sendto(listenfd,buf,n,0,(struct sockaddr*)&client,sizeof(client));
      if(s==0)
	  {
	     perror("use sendto");
		 exit(3); 
	  } 
  } 
  close(listenfd);
  return 0;
} 
