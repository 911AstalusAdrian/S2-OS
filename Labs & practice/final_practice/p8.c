#include <stdio.h>
#include <unistd.h>
int main(int argc, char** argv) {
 printf("A\n");
 execl("grep", "grep", "-E", "/an1/gr211/", "/etc/passwd", NULL);
 printf("B\n");
 return 0;
}

