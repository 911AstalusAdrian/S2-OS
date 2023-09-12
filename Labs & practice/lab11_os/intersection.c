#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define N 50

sem_t four_lane, two_lane;
pthread_barrier_t b, 

void* car(void* a){
	int id = *(int*)a;
	int lane = id%2;
	printf("Car %d is on lane %d\n", id, lane);
	pthread_barrier_wait(&b);
	if(lane == 0){
		sem_wait(&four_lane);
		printf("Car %d from lane %d passed\n", id, lane);
		sem_post(&two_lane);
	}
	else{
		sem_wait(&two_lane);
		printf("Car %d from lane %d passed\n", id, lane);
		sem_post(&two_lane);
	}
	return NULL;
}

int main(){
	pthread_t p[N];
	sem_init(&four_lane, 0, 8);
	sem_init(&two_lane, 0, 3);
	int i;
	pthread_barrier_init(&b, NULL, N);
	for(i=0;i<N;i++){
		int  *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&p[i], NULL, car, v) != 0){
			perror("could not create thread");
			exit(1);
		}
	}
	
	for(i=0;i<N;i++)
		pthread_join(p[i], NULL);
	sem_destroy(&four_lane);
	sem_destroy(&two_lane);
	pthread_barrier_destroy(&b);
	return 0;
}
