#include"head.h" 
int Socket(int domain,int type,int protocol)
{
    int fd=socket(domain,type,protocol);
	   if(fd<=0)
		{
		    perror("use socket");
			exit(-1); 
		} 
     return fd;
} 
int Bind(int sockfd,const struct sockaddr* addr,socklen_t addrlen)
{	
       int bd=bind(sockfd,addr,addrlen);
	   if(bd<0)
	   {
	      perror("use bind");
		  exit(1); 
	   } 
	   return bd;
}
int Listen(int sockfd,int backlog)
{
    int ls=listen(sockfd,backlog);
	if(ls<0)
	{
	   perror("use listen");
	   exit(1); 
	} 
	return ls;
} 
int Accept(int sockfd,struct sockaddr* addr,socklen_t* addrlen)
{

int n;
  again:
  if ((n = accept(sockfd,addr, addrlen)) < 0) 
  {
		  if ((errno == ECONNABORTED )||(errno == EINTR))
					goto again;
		  else
						perror("accept error");
		                exit(-1); 
			}
  return n;
}  
int Connect(int Sockfd,const struct sockaddr* addr,socklen_t addrlen)
{
    int co=connect(Sockfd,addr,addrlen);
	if(co<0)
	{
	   perror("use connect");
	   exit(1); 
	} 
} 



