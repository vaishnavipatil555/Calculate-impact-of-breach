#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(){
	struct sockaddr_in server, client;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	if(sockfd == -1){
		printf("Socket creation error\n");
		exit(0);
	}
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.43.17");
	server.sin_port = htons(1027);

	if((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) != 0){
		printf("Socket bind failed!\n");
		exit(0);
	}
	
	if((listen(sockfd, 5)) != 0){
		printf("Listen failed!");
		exit(0);
	}

	int len = sizeof(client);
	int connfd = accept(sockfd, (struct sockaddr*)&client, &len);
	if(connfd < 0){
		printf("Server accept failed!\n");
		exit(0);
	}
	char buff[1024];
	read(connfd, buff, sizeof(buff));
	printf("%s\n", buff);
	close(connfd);
	close(sockfd);
	return 0;
}
