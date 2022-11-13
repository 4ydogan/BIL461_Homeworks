#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// states
#define HUNGRY 0
#define BUTTERMILK 1
#define EATING 2
#define THINKING 3

pthread_mutex_t lock;

//arrays
int *phil;
int *eating;
int *state;

// global variables
int k = 0;
int count = 0;
int stack = 0;

// method definition
int createThreads(pthread_t *philosophers, int n);
int push();
int pop();
int print();
int createRandom(int n);
int eat_and_think(int num);
int take_buttermilk(int num);
void* philosopher(void* num);

int main(int argc, char **argv){

	// take philosopher count
	printf("Please enter count of philosophers (it must be integer): ");
	scanf("%d", &count);

	// array memory allocation
	phil = malloc(sizeof(int) * count);
	eating = malloc(sizeof(int) * count);
	state = malloc(sizeof(int) * count);

	// thread array allocation
	pthread_t *philosophers = malloc(sizeof(pthread_t) * count);

	// array initial assign
	for (int i = 0; i < count; i++) {
		phil[i] = i;
		eating[i] = 0;
		state[i] = HUNGRY;
	}

  	if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

	push();

	// creating threads
    createThreads(philosophers, count);

	pthread_mutex_destroy(&lock);
	return 0;
}

// ---------- methods --------------

// philosopher method
void* philosopher(void* num) {
	int num_of_philosopher = *(int *) num;
	int left  = (num_of_philosopher - 1 + count) % count;
	int right = (num_of_philosopher + 1) % count;
	
	while (1) {

		// if buttermilk is run out of
		pthread_mutex_lock(&lock);
		if (stack == 0) {
			print();
			push();
		}
		pthread_mutex_unlock(&lock);

		// take buttermilk if the philosopher is hungry
		if (state[num_of_philosopher] == HUNGRY) {
			take_buttermilk(num_of_philosopher);
		}

		// check left and right philosopher; if the philosopher has buttermilk, eat and think
		if (state[num_of_philosopher] == BUTTERMILK && state[left] != EATING && state[right] != EATING) {
			eat_and_think(num_of_philosopher);
		}
			
		sleep(1);
	}
	
}

// updates num'th philosopher state
int eat_and_think(int num){

	pthread_mutex_lock(&lock);
	state[num] = EATING;
	pthread_mutex_unlock(&lock);

	// sleep 1-5 second
	sleep(createRandom(1));
	eating[num]++;

	pthread_mutex_lock(&lock);
	state[num] = THINKING;
	pthread_mutex_unlock(&lock);

	// sleep 1-5 second
	sleep(createRandom(1));

	pthread_mutex_lock(&lock);
	state[num] = HUNGRY;
	pthread_mutex_unlock(&lock);
}

// updates num'th philosopher state as buttermilk
int take_buttermilk(int num){

	pthread_mutex_lock(&lock);
	stack--;
	state[num] = BUTTERMILK;
	pthread_mutex_unlock(&lock);
}

// creates a random integer between 1-n
int createRandom(int n){
	srand(time(NULL));
	return rand() % (5*n) + 1;
}

// add buttermilk
int push(){
	k = createRandom(count);
	stack = k;

	printf("\n--------------------------\n");
	printf("Added %d glasses buttermilk.\n", k);
	printf("--------------------------\n");
}

// create n thread and join
int createThreads(pthread_t *philosophers, int n){
	int error = 0;
  	int i = 0;
    while (i < n) {
        if (pthread_create(&(philosophers[i]), NULL, philosopher, (void *) &phil[i]) != 0){
			printf("\nThread creating has failed\n");
			exit(1);
		}
        i++;
    }

    i = 0;
    while (i < n) {
        pthread_join(philosophers[i], NULL);
        i++;
    }
}

// print the how many time eating and sleep 5 second
int print(){

	for (int i = 0; i < count; i++)
	{
		printf("%dth philosopher ate %d portion.\n", i+1, eating[i]);
		eating[i] = 0;
	}

	sleep(5);
}