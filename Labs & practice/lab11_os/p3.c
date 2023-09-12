#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t b;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* s(void*a){
	int i = *(int*) a;
	printf("slow thread %d started\n", i);
	sleep(rand()%6+5);
	printf("Slow thread %d waiting\n", i);
	pthread_barrier_wait(&b);
	pthread_mutex_unlock(&mutex);
	printf("Slow phase 2 done\n");
	free(a);
	return NULL;
}

void* f(void*a){
	printf("Fast thread started\n");
	sleep(rand()%2+2);
	printf("Fast phase 1 done\n");
	printf("Fast thread waiting\n");
	pthread_mutex_lock(&mutex);
	printf("Phase 2 done\n");
	pthread_mutex_unlock(&mutex);
	printf("Fast thread done\n");
	return NULL;
}

int main(int argc, char** argv){
	pthread_t slow[5], fast;
	pthread_barrier_init(&b, NULL, 5);
	int i;
	for(i=0;i<5;i++){
		int* v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&slow[i], NULL, s, v) != 0){
			perror("Could not create thread");
			exit(1);
		}
	}
	if(pthread_create(&fast, NULL, f, NULL) != 0){
		perror("could not create thread");
		exit(1);
	}
	for(i=0;i<5;i++)
		pthread_join(slow[i], NULL);
	pthread_join(fast, NULL);
	pthread_barrier_destroy(&b);
	return 0;
}
