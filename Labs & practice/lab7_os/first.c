#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[]){
  int LEN=100;
  int c2p[2], i;
  for(i=0;i<argc;i++)
    printf("i: %d a: %s\n", i, argv[i]);
  //exit(0);
  if(pipe(c2p)<0){
    perror("Unable to create the channel");
    exit(1);
  }
  int f=fork();
  if(f<0){
    perror("Unable to create the copy");
    exit(2);
  }
  if(f==0){
    close(c2p[0]);
    dup2(c2p[1], STDOUT_FILENO);
    if(execl(argv[1],argv[1],NULL)<0){
      perror("Unable to execute");
      close(c2p[1]);
      exit(3);
    }     	
  }
  wait(0);
  close(c2p[1]);
  char* buffer = malloc(LEN*sizeof(char));
  int b=read(c2p[0], buffer, LEN-1);
  if(b<0){
    perror("Could not read");
    exit(4);
  }
  buffer[b]=0;
  printf("Recieved: %s\n", buffer);  
  close(c2p[0]); 
  return 0;
}
