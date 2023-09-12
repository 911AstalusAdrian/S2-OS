//3. Write a C program that creates two child processes. 
//The two child processes will alternate sending random integers between 1 and 10(inclusively) 
//to one another until one of them sends the number 10. 
//Print messages as the numbers are sent.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){

	int a2b[2], b2a[2];
	pipe(a2b);
	pipe(b2a);
	if(fork() == 0){ // A
		close(a2b[0]); // we do not read from A
		close(b2a[1]); // we do not write from B
	       // srand(time(0));
		while(1){
	                int from_b;
        	        read(b2a[0], &from_b, sizeof(int));
	                printf("From B: %d\n", from_b);

			int nr=0;
			srand(time(0));
			nr = random()%10+1;
			if(nr == 10){
				printf("10 found in A\n");
				break;
			}
			write(a2b[1], &nr, sizeof(int));
			printf("A sends to B: %d\n", nr);
			sleep(2);
		}
		close(a2b[1]);
		close(b2a[0]);
		exit(0);
			
	}

	if(fork() == 0){ // B
		close(a2b[1]); // we do not write from A
		close(b2a[0]); // we do not read from B
		while(1){
                	int from_a;
        	        read(a2b[0], &from_a, sizeof(int));
	                printf("From A: %d\n", from_a);

			int nr2=0;
			srand(time(0));
			nr2 = random()%10+1;
			if(nr2 == 10){
				printf("10 found in B\n");
				break;
			}
			write(b2a[1], &nr2, sizeof(int));
			printf("B sends to A: %d\n", nr2);
			sleep(2);
		}	
		close(a2b[0]);
		close(b2a[1]);
		exit(0);
	}
	int a=0;
	write(b2a[1], &a, sizeof(int));
	write(a2b[1], &a, sizeof(int));
	close(a2b[1]);
	close(a2b[0]);
	close(b2a[1]);
	close(b2a[0]);
	wait(0);
	wait(0);
	return 0;
}
