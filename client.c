#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(){
	int sockfd, connfd;
	struct sockaddr_in server, client;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Socket creation failed\n");
		exit(0);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.43.17");
	server.sin_port = htons(1027);
	if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0){
		printf("Connection failed\n");
		exit(0);
	}
	char buff[] = "Hello";
	write(sockfd, buff, sizeof(buff));
	close(sockfd);
	return 0;
}
