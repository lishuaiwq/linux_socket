#include"head.h"
#define SERVE_IP "192.168.240.129"
#define SERVE_PORT 9526

struct sin
{
   struct sockaddr_in pthaddr;
   int cfd;
}; 
void* funtion(void *arg)
{
	pthread_detach(pthread_self()); 
    struct sin *sin_fun=(struct sin*)arg;
	char c_ip[32]={0};  
	inet_ntop(AF_INET,(void*)&sin_fun->pthaddr.sin_addr.s_addr,c_ip,sizeof(sin_fun->pthaddr));
	printf("client ip=%s   prot=%d\n",c_ip,ntohs(sin_fun->pthaddr.sin_port));
    while(1)
	{
	  int i=0;		
	  char buf[1024]={0}; 
	  int n=read(sin_fun->cfd,buf,sizeof(buf));
	  if(n==0)
	  {
	      pthread_exit((void*)-1);  
	  } 
	  printf("client:%s",buf); 
	  for(;i<n;i++)
			  buf[i]=toupper(buf[i]);
	  write(sin_fun->cfd,buf,n); 
	} 
	close(sin_fun->cfd); 
} 
int main()
{
	int number=1;	
	pid_t pid;		
	int i=0;
	struct sin pthread_sin[1024]; 
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
	pthread_t tid;
	cfd=Accept(sfd,(struct sockaddr*)&c_addr,&len);
	pthread_sin[i].cfd=cfd;
	pthread_sin[i].pthaddr=c_addr; 
    pthread_create(&tid,NULL,funtion,(void *)&pthread_sin[i]); 
     i++;
	} 
      
}
