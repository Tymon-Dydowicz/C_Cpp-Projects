#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

#define N 4 // SIZE OF BUFFERS/QUEUES
#define time_step 5 //MAX NUMBERS OF SECONDS SLEEPING

int main() {
	srand(time(NULL));
	int fd, i, v, counter1, arr_full, arr_empty, creation_index, consuming_index, num;
	char *buffer, *full, *empty;   //, *counter; , *test;
	int *test, *counter;
	sem_t *Sem_prod, *Sem_cons, *Sem_Q_prod, *Sem_Q_cons;

	//Checking how many producers are already running
	num =shm_open("/num", O_CREAT|O_RDWR);
	ftruncate(num, sizeof(int));
	test = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, num, 0);

	//COUNTER INDICES 0=Producer addition index; 1=Producer removal index; 2=Consumer additon index; 3=Consumer removal index
	counter1 = shm_open("/counter", O_CREAT|O_RDWR);
	ftruncate(counter1, 4*sizeof(int));
	counter = mmap(NULL, 4*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, counter1, 0);

	//Buffer containing the items
	fd = shm_open("/buffer", O_CREAT|O_RDWR, 0600);
	ftruncate(fd, N*sizeof(int));
	buffer = mmap(NULL, N*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	//List of indexes of non empty buffer slots
	arr_full = shm_open("/arr_full", O_CREAT|O_RDWR, 0600);
	ftruncate(arr_full, N*sizeof(int));
	full = mmap(NULL, N*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, arr_full, 0);

	//List of indexes of empty buffer slots
	arr_empty = shm_open("/arr_empty", O_CREAT|O_RDWR, 0600);
	ftruncate(arr_empty, N*sizeof(int));
	empty = mmap(NULL, N*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, arr_empty, 0);


	if (buffer == MAP_FAILED || empty == MAP_FAILED || full == MAP_FAILED || counter == MAP_FAILED || test == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	Sem_prod = sem_open("/Sem_prod", O_CREAT, 0600, N);
	Sem_cons = sem_open("/Sem_cons", O_CREAT, 0600, 0);
	Sem_Q_prod = sem_open("/Sem_Q_prod", O_CREAT, 0600, 1);
	Sem_Q_cons = sem_open("/Sem_Q_cons", O_CREAT. 0600, 1);
	if (Sem_prod==SEM_FAILED || Sem_cons==SEM_FAILED || Sem_Q_prod==SEM_FAILED || Sem_Q_cons == SEM_FAILED) perror("sem_open");

	//INITIALIZING SOME OF THE DATA for producers only
	/*if (test++ == 0){
		v=1;
		for (int i = 0; i < 4: i++){
			counter[i] = 0;
		}
		for (int i = 0; i < N: i++){
			empty[i] = i;
		}
	}*/



	while(1) {
		int time = rand()%time_step;  //TIME RANDOMIZER


		sem_wait(Sem_cons); //Decresing consumer semaphore

		
		sem_wait(Sem_Q_cons); //Entering the consumer index Q and locking the binary semaphore
		consuming_index = full[counter[3]]; //Getting the index
		counter[3] = (counter[3]+1)%N; //Incrementing the removal counter and looping it around
		sem_post(Sem_Q_cons); //Leaving the Q allowing other processes to enter

		//CREATION PROCESS
		printf("Consuming: buffer[%d]\n", consuming_index);
		buffer[consuming_index] = 0;
		sleep(time);

		sem_wait(Sem_Q_prod); //Entering the producer index Q and locking the binary semaphore
		empty[counter[0]] = consuming_index //Giving the index of recently emptied buffer index for producers
		counter[0] = (counter[0]+1)%N; //Incrementing the addition counter and looping it around
		sem_post(Sem_Q_prod); //Leaving the Q allowing other processes to enter


		sem_post(Sem_prod); //Increasing producer semaphore
	}

	sem_close(Sem_prod);
	sem_close(Sem_cons);
	sem_close(Sem_Q_cons);
	sem_close(Sem_Q_prod);
	sem_unlink("/Sem_prod");
	sem_unlink("/Sem_cons");
	sem_unlink("/Sem_Q_cons");
	sem_unlink("/Sem_Q_prod");
	munmap(buffer, N*sizeof(int));
	munmap(full, N*sizeof(int));
	munmap(empty, N*sizeof(int));
	munmap(counter, 4*sizeof(int));
	munmap(test, sizeof(int));
	return 1;
}
