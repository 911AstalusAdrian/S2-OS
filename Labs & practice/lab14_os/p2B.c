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
	char* input = (char*)malloc(sizeof(char)*MAX_LEN);
	
	int fd = open(FIFO, O_WRONLY);
	if (fd < 0){
		perror("error on opening fifo");
		exit(2);
	}
	int len;
	if(read(fd, &len, sizeof(int)) < 0){
		perror("error on sending len");
		exit(3);
	}

	if(read(fd,input,sizeof(char)*(len+1)) < 0){
		perror("error on sending the input");	
		exit(4);
	}
	input[len]=0;
	printf("%s\n", input);
	free(input);
	return 0;
}
