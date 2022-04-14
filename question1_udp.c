
//server code for upd
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int sockfd , retval,n;
	socklen_t clilen;
	struct sockaddr_in cliaddr , servaddr;
	char buf [10000];
	
	sockfd= socket(AF_INET , SOCK_DGRAM, 0);
	if(sockfd<0)
	{
		perror("sock:");
		exit(1);
		
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);
	retval = bind(sockfd, (struct sockaddr *) &servaddr , sizeof(servaddr));
	if(retval <0)
	{
		perror("bind:");
		exit(2);
	}
	//(sockfd, 5);
	
	clilen = sizeof(struct sockaddr_in);
	
	while(1)
	{	
		printf(" before vreceive \n");
	
		//clilen = sizeof(cliaddr);
		n = recvfrom(sockfd, buf,10000,0,(struct sockaddr *)&cliaddr ,&clilen);
		
		//connfd = accept(listfd , (struct sockaddr *) &cliaddr , &clilen);
		printf("REC'D %d bytes \n", n);
		buf[n] ='\0';
		
		printf("msg from client = %s\n", buf);
		
		
	}
	//close(sockfd);
	//close (listfd);
	
}




//************client code for udp ******

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char *serv_ip = "127.0.0.1";
	char *msg = "abcdefghijklmno";
	//int sockfd , ret_val;
	
	int sockfd , ret_val;
	socklen_t addr_len;
	struct sockaddr_in servaddr;
	sockfd = socket (AF_INET , SOCK_DGRAM ,0);
	if(sockfd <0)
	{
		perror("error:");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	//servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8000);
	inet_pton(AF_INET, serv_ip , &servaddr.sin_addr);
	addr_len = sizeof(struct sockaddr_in);
	
	ret_val = sendto(sockfd , msg,strlen(msg),0,(struct sockaddr *) &servaddr , addr_len);
	printf(" ret val of send to = %d \n", ret_val);
	
	close(sockfd);
	}

