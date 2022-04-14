//server code for tcp

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int listfd, connfd , retval;
	pid_t childpid;
	
	socklen_t clilen;
	struct sockaddr_in cliaddr , servaddr;
	listfd = socket(AF_INET , SOCK_STREAM, 0);
	if(listfd <0)
	{
		perror("sock:");
		exit(1);
		
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8000);
	retval = bind(listfd, (struct sockaddr *) &servaddr , sizeof(servaddr));
	if(retval <0)
	{
		perror("bind:");
		exit(2);
	}
	listen(listfd, 5);
	while(1)
	{	char buf[200];
		int n;
		//clilen = sizeof(cliaddr);
		
	
		clilen = sizeof(cliaddr);
		connfd = accept(listfd , (struct sockaddr *) &cliaddr , &clilen);
		printf("client connected \n");
		n = read(connfd , buf , 200);
		buf[n] = '\0';
		printf("data rec 'd from client  = %s \n", buf);
		write(connfd , "goodbye", 8);
		
		
	}
	close (listfd);
	
}




//*****client code for tcp************


#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char buf[200];
	int n;
	char *serv_ip = "127.0.0.1";
	int sockfd , ret_val;
	struct sockaddr_in servaddr;
	sockfd = socket (AF_INET , SOCK_STREAM ,0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	//servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8000);
	inet_pton(AF_INET, serv_ip , &servaddr.sin_addr);
	ret_val = connect(sockfd , (struct sockaddr *) &servaddr , sizeof(servaddr));
	if(ret_val <0)
	{
		perror("connect:");
		exit(1);
	}
	//char buf[200];
	//int n;
	
	printf("enter the data that you want to send the server \n");
	//close(sockfd);
	gets(buf);
	write(sockfd, buf , strlen(buf));
	n = read(sockfd , buf , 200);
	buf[n] = '\0';
		printf("data rec 'd from server  = %s \n", buf);
		close(sockfd);
		//write(connfd , "goodbye", 8);
	}


