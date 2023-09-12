//Create two processes A and B. 
//A generates a random number n between 50 and 200. 
//If it is even, it sends it to B, if it is odd it sends n+1 to B. 
//B receives the number and divides it by 2 and sends it back to A. 
//The process repeats until n is smaller than 5. 
//The processes will print the value of n at each step.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char** argv){
	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);
	if(fork() == 0){
		close(p2c[1]);
		close(c2p[0]);
		int nrp;
		while(1){
			read(p2c[0], &nrp, sizeof(int));
			nrp /= 2;
			write(c2p[1], &nrp, sizeof(int));
			if(nrp<5)
				break;
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}
	close(p2c[0]);
	close(c2p[1]);
	int nr;
	srandom(time(NULL));
	nr = rand()%151+50;
	while(nr >= 5){
		if(nr%2==1)
			nr++;
		printf("P-> %d\n", nr);
		write(p2c[1], &nr, sizeof(int));
		read(c2p[0], &nr, sizeof(int));
		printf("P<- %d\n", nr);
	}
	wait(0);
	close(p2c[1]);
	close(c2p[0]);
	return 0;
}
