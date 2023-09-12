#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FIFO "f"
#define MAX_LEN 100
int main(){
	if(mkfifo(FIFO, 0600) == -1){
		perror("error on creating fifo");
		exit(1);
	}
	printf("provide input:");
	char* input = (char*)malloc(sizeof(char)*MAX_LEN);
	scanf("%100s", input);
	
	int fd = open(FIFO, O_WRONLY);
	if (fd < 0){
		perror("error on opening fifo");
		exit(2);
	}
	int len = strlen(input);
	if(write(fd, &len, sizeof(int)) < 0){
		perror("error on sending len");
		exit(3);
	}

	if(write(fd,input,sizeof(char)*len) < 0){
		perror("error on sending the input");	
		exit(4);
	}

	close(fd);
	unlink(FIFO);
	return 0;
}
