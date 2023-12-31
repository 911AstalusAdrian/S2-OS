#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEN 100
int main(){
	printf("Provide command:");
	
	char* command = (char*)malloc(sizeof(char)*LEN);
	scanf("%100s", command);
	
	int c2p[2];
	if(pipe(c2p) < 0){
		perror("error on creaing pipe");
		exit(1);
	}
		
	int f = fork();
	if( f < 0){
		perror("error on creating child");
		exit(1);
	}

	if(f == 0){
		close(c2p[0]);
		dup2(1, c2p[1]);
		if(execl(command, command,  NULL) < 0){
			perror("error on executing");
			exit(1);
		}
	}

	close(c2p[1]);
	char* result = (char*)malloc(sizeof(char)*(LEN+1));
	if(read(c2p[0], result, sizeof(char)*LEN) < 0){
		perror("error on reading result");
		exit(1);
	}

	result[LEN] = 0;
	printf("The result is: %s\n", result);
	close(c2p[0]);
	free(command);
	free(result);
	return 0;
}
