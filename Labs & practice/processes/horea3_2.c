#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include<time.h>

int main(int argc, char**argv){

        int n;

        srand(time(0));

        int a2b[2];
        int b2a[2];

        pipe(a2b);
        pipe(b2a);

        if(fork()==0){ //A
                close(b2a[1]);
                close(a2b[0]);

                while(1){
                        if(read(b2a[0], &n, sizeof(int))<= 0){
                                break;
                        }

                        if(n==10){
                                break;
                        }

                        printf("A: %d ", n);

                        n = (rand() % 10)+1;

                        printf("->> %d\n", n);

                        write(a2b[1], &n, sizeof(int));
                }

                close(a2b[1]);
                close(b2a[0]);
        }


        if(fork()==0){ //B
                close(b2a[0]);
                close(a2b[1]);

                while(1){
                        if(read(a2b[0], &n, sizeof(int))<= 0){
                                break;
                        }

                        if(n==10){
                                break;
                        }

                        printf("B: %d ", n);

                        n = (rand() % 10)+1;

                        printf("->> %d\n", n);

                        write(b2a[1], &n, sizeof(int));
                }

                close(b2a[1]);
                close(a2b[0]);
        }

        close(a2b[0]);
        close(b2a[1]);
        close(b2a[0]);

        n = (rand() % 10)+1;


        write(a2b[1], &n, sizeof(int));
        close(a2b[1]);

        wait(0);
        wait(0);


return 0;
}
