// Part 1 of the sum program
// Reads two numbers from the keyboard
// Sends them through FIFO to part two
// nclude <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// Recieves the sum of the numbers

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char** argv){
	int a2b, b2a;
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);
	int nr1, nr2, sum;
	printf("Give the two numbers\n");
	printf("Number 1~");
	scanf("%d", &nr1);
	printf("Number 2~");
	scanf("%d", &nr2);
	printf("Sending %d and %d to the second program...\n", nr1, nr2);
	write(a2b, &nr1, sizeof(int));
	write(a2b, &nr2, sizeof(int));
	printf("Numbers sent!\n");
	read(b2a, &sum, sizeof(int));
	printf("Recieved %d\n", sum);
	close(a2b);
	close(b2a);
	return 0;
}
