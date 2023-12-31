#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) { 
    if (argc != 2){
        printf("Please provide exactly one argument.\n");
        exit(1);
    } 
    int p_to_c[2], c_to_p[2];
    pipe(p_to_c);
    pipe(c_to_p);
    int f = fork();
    if(-1 == f) {
        perror("Error on fork ");
        exit(1);
    } else if (0 == f) {
        close(p_to_c[1]);
        close(c_to_p[0]);
        int n = 0, i, nr;
        float rez = 0;
        if(0 > read(p_to_c[0], &n, sizeof(int))) {
            perror("Error on read n from parent ");
            close(p_to_c[0]);
            close(c_to_p[1]);
            exit(1);
        }
        for(i = 0; i < n; i++) {
            if(0 > read(p_to_c[0], &nr, sizeof(int))) {
                perror("Error on read from parent ");
                close(p_to_c[0]);
                close(c_to_p[1]);
                exit(1);
            }
            rez += nr;
        }
        rez /= n;
        if(0 > write(c_to_p[1], &rez, sizeof(float))) {
            perror("Error on write result to parent ");
            close(p_to_c[0]);
            close(c_to_p[1]);
            exit(1);
        }
        close(p_to_c[0]);
        close(c_to_p[1]);
        exit(0);
    } else {
        close(p_to_c[0]);
        close(c_to_p[1]);
        int n = atoi(argv[1]);
        int i, nr;
        float rez = -1;
        srandom(time(0));
        if(0 > write(p_to_c[1], &n, sizeof(int))) {
            perror("Error on write n to child ");
            close(p_to_c[1]);
            close(c_to_p[0]);
            wait(0);
            exit(1);
        }
        for(i = 0; i < n; i++) {
            nr = random() % 100;
            printf("Parent generated %d\n", nr);
            if(0 > write(p_to_c[1], &nr, sizeof(int))) {
                perror("Error on write number to child ");
                close(p_to_c[1]);
                close(c_to_p[0]);
            }
        }
        wait(0);
        if(0 > read(c_to_p[0], &rez, sizeof(float))) {
            perror("Error on read result from child ");
        }
        printf("Average is %f\n", rez);
        close(p_to_c[1]);
        close(c_to_p[0]);
    }
    return 0;
}
