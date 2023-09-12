#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define N 3

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
void* ft(void* a){
	int idx;
	idx = (int)pthread_self();
	printf("Thread %d started\n", idx);
	int r = rand()%2+1;
	sleep(r);
	printf("Thread %d phase 1 done\n", idx);
	
	pthread_mutex_lock(&m); // m is locked
	pthread_cond_wait(&c,&m); // unlocks the mutex & registering the thread in the queue
	// mutex synchronises the mutexes in the queue
	// locks the mutex again
	
	printf("Thread %d started phase 2\n", idx);
	pthread_mutex_unlock(&m);
	
	return NULL;
}

void* st(void* a){
        int idx;
        idx = (int)pthread_self();
        printf("Slow thread %d started\n", idx);
	int r = rand()%2+3;
        sleep(r);
        printf("Slow thread %d phase 1 done\n", idx);
 
	pthread_cond_broadcast(&c); //releasing all the waiting threads
        printf("Slow thread %d phase 2 is done\n", idx);

	return NULL;
}

int main(){
	pthread_t t[N];
	int i;
	srand(time(NULL));
	for(i=0;i<N-1;i++){
		if(pthread_create(&t[i], NULL, ft, NULL)!=0){
			perror("error");
			exit(1);
		}
	}	
	if(pthread_create(&t[i],NULL,st,NULL)!=0){
		perror("Error on create");
		exit(1);
	}
	for(i=0;i<N;i++)
		pthread_join(t[i], NULL);
	return 0;
}
