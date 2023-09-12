// Part 2 of the program
// Recieves two numbers and calculates their sum
// Sends the sum to the program A

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char** argv){
	int a2b, b2a;
	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);
	int a, b, s;
	read(a2b, &a, sizeof(int));
	read(a2b, &b, sizeof(int));
	s = a+b;
	write(b2a, &s, sizeof(int));
	close(a2b);
	close(b2a);
	return 0;
}
