#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
       #include <sys/types.h>
       #include <sys/wait.h>

int main(){
	fork();
	printf("Hey\n");
	wait(0);
	fork();
	printf("Hey\n");
	wait(0);
	fork();
	printf("Hey\n");
	return 0;
}
