/*
 * @author: Jordi Jaspers
 * @date 06/04/2020
 * @title: Excercise_2 preventing problem
*/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h> 
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUMBER_OF_THREADS 5
#define MAX_COUNT 50000

static sem_t obj_produced;
static sem_t obj_consumed;

static int shelf;
pthread_mutex_t m_lock;

void * producer() {
  int i;
  
  for(i=2; i< MAX_COUNT; i++) {
    pthread_mutex_lock(&m_lock);
    shelf = i;
    sem_post(&obj_produced);
    sem_wait(&obj_consumed);
    pthread_mutex_unlock(&m_lock);
  }

  return NULL;
}


void * consumer(void *ID) {
    //declare local variable
    unsigned char isPrime;
    int i;
    int VUT;
    int *localID = (int *)ID;

    // creating a FILE variable
    FILE *fptr;
    
    // open the file in write mode
    if((fptr=freopen("terminal_output", "w" ,stdout))==NULL) {
    printf("Cannot open file.\n");
    exit(1);
    }



    while(1) {
        sem_wait(&obj_produced);
        VUT = shelf;
        sem_post(&obj_consumed);
        printf("[CONSUMER ID: %d]: %d\n", *localID, VUT);

        isPrime = 1;
        for (i=2;i<VUT; i++) {
            if (VUT % i ==0) {
                isPrime = 0;
            }
        }
        if(isPrime==1) {
            printf("    thread #%d announces that %d is prime.\n", *localID, i);
        }
    }

    // close connection
    fclose(fptr);
}


int main(void) {
  int i = 0, err;
  pthread_t tid[NUMBER_OF_THREADS];

  // create semaphores
  err = sem_init(&obj_produced, 0, 0);
  if(err != 0) {
    printf("\ncan't create semaphore: obj_produced [%s]", strerror(err));
    return 1;
  }
  err = sem_init(&obj_consumed, 0, 0);
  if(err != 0) {
    printf("\ncan't create semaphore: obj_produced [%s]", strerror(err));
    return 1;
  }

  // create producer thread
  err = pthread_create(&(tid[i]), NULL, &producer, NULL);
  if (err != 0) {
    printf("\ncan't create producer thread: [%s]", strerror(err));
    return 1;
  } 
  printf("Producer thread created\n");

  // create consumer threads
  int IDArray [NUMBER_OF_THREADS];

  for(i=1;i<NUMBER_OF_THREADS;i++) {
    IDArray[i] = i;
    err = pthread_create(&(tid[i]), NULL, &consumer, &IDArray[i]);
    if (err != 0) {
      printf("\ncan't create consumer thread %d: [%s]", i, strerror(err));
    }
    printf("Consumer thread %d created\n", i);
  }

  // wait for producer thread
  pthread_join(tid[0], NULL);

  // kill consumer threads 
  for(i=1;i<NUMBER_OF_THREADS;i++) {
    pthread_kill(tid[i], 9);
  }

  // delete the semaphores
  sem_destroy(&obj_produced);
  sem_destroy(&obj_consumed);

  return 0;
}