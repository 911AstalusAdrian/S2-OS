// Create a C program that generates N random integers (N given at the command line). It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>      
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv){
	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);
	if(fork() == 0){
		close(p2c[1]);
		close(c2p[0]);
		int count=0, n, nr=0, i, sum=0;
		float avg;
		read(p2c[0], &n, sizeof(int));
		for(i=0; i<n; i++){
			read(p2c[0], &nr, sizeof(int));
			sum = sum+nr;
			count = count+1;
		}
		avg = (float)sum/(float)count;
		write(c2p[1], &avg, sizeof(float));
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}
	close(p2c[0]);
	close(c2p[1]);
	int n = atoi(argv[1]);
	write(p2c[1], &n, sizeof(int));
	int j, nr;
	for(j=0;j<n;j++){
		nr = random()%100;
		printf("%d\n", nr);
		write(p2c[1], &nr, sizeof(int));
	}
	wait(0);
	float rez=-1;
	read(c2p[0], &rez, sizeof(float));
	printf("%f\n", rez);
	close(p2c[1]);
	close(c2p[0]);
	return 0;
}
