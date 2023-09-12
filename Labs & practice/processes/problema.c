// Se scrie un program care citeste un numar de la tastatura
// genereaza atatea numere aleatorii cat este valoarea citita de la tastatura
// creeaza un proces fiu, trimite numerele aleatorii generate fiului
// Fiul dupa ce primeste toate numerele de la parinte le va trimite acestuia
// in ordine inversa

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
int main(){
	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);
	int n, r, i;
	printf("n is:");
	scanf("%d", &n);
	write(p2c[1], &n, sizeof(int));
	srandom(time(0));
	for (i=0;i<n;i++){
		r = rand()%50;
		write(p2c[1], &r, sizeof(int));	
	}
	close(p2c[1]);
	if(fork() == 0){
		close(p2c[1]);
		close(c2p[0]);
		int m, i;	
		read(p2c[0], &m, sizeof(int));
		int array[m+1];
		for(i=0;i<m;i++){
			read(p2c[0], &array[i], sizeof(int));
		}
		printf("Recieved:\n");
		for(i=0;i<m;i++){
			printf("%d ", array[i]);
		}
		printf("\n");
		for(i=m-1;i>=0;i--)
			write(c2p[1], &array[i], sizeof(int));

		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}
	wait(0);
	printf("Reversed:\n");
	for(i=0;i<n;i++){
		read(c2p[0], &r, sizeof(int));
		printf("%d ", r);
	}
	printf("\n");
	close(c2p[0]);
	return 0;
}
