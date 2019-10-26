#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int readline(char **line, int fd) {
	int size, i;
	char ch;
	i = 0;
	size = 128;
	*line = (char *)malloc(sizeof(char) * size);
	while(read(fd, &ch, 1)) {
		if(ch == '\n' || ch == '\0') {
			(*line)[i] = '\0';
			return i;
		}
		(*line)[i++] = ch;
		if(i > size) {
			size *= 2;
			*line = (char *)realloc(*line, sizeof(char) * size);
		}
	}
	(*line)[i] = '\0';
	return i;
}
int search(char **IPs, char *token, int size_IP) {
	int i;
	for(i = 0; i < size_IP; i++) {
		if(strcmp(IPs[i], token) == 0) {
			return i;
		}
		else {
			continue;
		}
	}
	
	return -1;
}
int get_dig(int num) {
	int len = 0;
	if(num < 10) {
		return 1;
	}
	if(num < 100) {
		return 2;
	}
	return 3;
}
int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage: test.c testfilename\n");
		return 0;
	}
	FILE *fd;
	int fp, x, i, index, size_IP = 0, size_IP_old, length, j;
	char *line, *token, sip[15] = " ", sip2[15], **IPs, *sourceIP, *testfile, protocol, *is_allow;
	testfile = (char *)malloc(sizeof(char) * strlen(argv[1]));
	strcpy(testfile, argv[1]);
	fp = open(testfile, O_RDONLY);
	if(fp == -1) {
		printf("Unable to open file\n");
		return (errno);
	}
	i = 0;
	x = readline(&line, fp);
	free(line);
	IPs = (char **)malloc(sizeof(char *) * 50);
	while(x = readline(&line, fp)) {
		token = strtok(line, ",");
		//if token not in IPs
		index = search(IPs, token, size_IP);
		if(size_IP % 15 == 0 && size_IP != 0) {
			IPs = (char **)realloc(IPs, sizeof(char*) * (2 * size_IP));
		}
		if(index == -1) {
			IPs[i] = token;
			size_IP++;
		}
		else {
			continue;
		}
		i++;
	}
	close(fp);
	size_IP_old = size_IP;
	//read again
	fd = fopen("info.txt", "w+");
	fp = open(testfile, O_RDONLY);
	if(fp == -1) {
		printf("Unable to open file\n");
		return (errno);
	}
	x = readline(&line, fp);
	length = get_dig(size_IP);
	
	sourceIP = (char *)malloc(sizeof(char) * (length + 2));
	while(x = readline(&line, fp)) {
		token = strtok(line, ",");
		strcpy(sip2, token);
		if(strcmp(sip, sip2) != 0){
			if(strcmp(sip, " ") != 0){
				fprintf(fd, "\n");
			}
			strcpy(sip, sip2);
		}
		token = strtok(NULL, ",");
		//if token not in IPs
		index = search(IPs, token, size_IP);
		if(index == -1 && strcmp(token, "ANY") != 0){
			if(size_IP % 50 == 0) {
				IPs = (char **)realloc(IPs, sizeof(char *) * (2 * size_IP));
			}
			IPs[size_IP++] = token;
			//i++;
			index = search(IPs, token, size_IP);
		}
		if(index != -1) {
			token = strtok(NULL, ",");
			if(strcmp(token, "ICMP") == 0 || strcmp(token, "ANY") == 0){
				is_allow = strtok(NULL, ",");
			}
			else{
				is_allow = strtok(NULL, ",");
				is_allow = strtok(NULL, ",");
			}
			if(strcmp(is_allow, "DENY") == 0 || strcmp(is_allow, "DENY_ALL") == 0) {
				continue;
			}
			if(strcmp(token, "TCP") == 0) {
				protocol = 't';

			}
			else if(strcmp(token, "UDP") == 0) {
				protocol = 'u';
			}
			else if(strcmp(token, "ICMP") == 0) {
				protocol = 'i';
			}
			else if(strcmp(token, "ANY") == 0){
				sprintf(sourceIP, "%dta", index);
				fprintf(fd, "%s ", sourceIP);
				sprintf(sourceIP, "%dua", index);
				fprintf(fd, "%s ", sourceIP);
				sprintf(sourceIP, "%dia", index);
				fprintf(fd, "%s ", sourceIP);
				continue;
			}
			sprintf(sourceIP, "%d%ca", index, protocol);
			fprintf(fd, "%s ", sourceIP);
		}
		else {
			if(strcmp(token, "ANY") == 0) {
				token = strtok(NULL, ",");
				if(strcmp(token, "ICMP") == 0 || strcmp(token, "ANY") == 0){
					is_allow = strtok(NULL, ",");
				}
				else{
					is_allow = strtok(NULL, ",");
					is_allow = strtok(NULL, ",");
				}
				if(strcmp(token, "ANY") == 0){
					if(strcmp(is_allow, "DENY_ALL") || strcmp(is_allow, "DENY") == 0) {
						continue;
					}
					else {
						for(j = 0; j < size_IP; j++){
							sprintf(sourceIP, "%dta", j);
							fprintf(fd, "%s ", sourceIP);
						}
						for(j = 0; j < size_IP; j++){
							sprintf(sourceIP, "%dua", j);
							fprintf(fd, "%s ", sourceIP);
						}
						for(j = 0; j < size_IP; j++){
							sprintf(sourceIP, "%dia", j);
							fprintf(fd, "%s ", sourceIP);
						}
						continue;
					}
				}
				else if(strcmp(token, "TCP") == 0) {
					protocol = 't';
				}
				else if(strcmp(token, "UDP") == 0) {
					protocol = 'u';
				}
				else if(strcmp(token, "ICMP") == 0) {
					protocol = 'i';
				}
				if(strcmp(is_allow, "DENY_ALL") == 0  || strcmp(is_allow, "DENY") == 0){
					continue;
				}
				else{
					for(j = 0; j < size_IP; j++){
						sprintf(sourceIP, "%d%ca", j, protocol);
						fprintf(fd, "%s ", sourceIP);
					}					
				}
				
			}
			else
				continue;
		}
	}
	free(sourceIP);
	close(fp);
	size_IP_old = size_IP - size_IP_old;
	//printf("%d\n", size_IP_old);
	for(j = 0; j < size_IP_old; j++) {
		fprintf(fd, "\n");
	}
	close(fp);
	fclose(fd);
	//free(line);
	fp = open("IPnames.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fp == -1) {
		printf("Unable to open file\n");
		return (errno);
	}
	for(j = 0; j < size_IP; j++) {
		sourceIP = malloc(sizeof(char) * (strlen(IPs[j]) + 1));
		strcpy(sourceIP, IPs[j]);
		write(fp, strcat(sourceIP, "\n"), strlen(IPs[j]) + 1);
		free(sourceIP);
	}
	for(j = 0; j < i; j++) {
		free(IPs[j]);
	}
	free(IPs);
	free(testfile);
	return 0;
}
