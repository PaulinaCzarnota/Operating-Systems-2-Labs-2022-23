/*

Lab Test 2    A semaphore implementation of the producer consumer problem

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>   // Use angle brackets for system headers

#define BUFF_SIZE 10    // global variable for the SIZE of the bounded buffer 

char buffer[BUFF_SIZE];   // the bounded buffer - to be implemented as a circular buffer
int nextIn = 0;    //producer index pointer 
int nextOut = 0;   // consumer index pointer

int times;       // the number of producer/consumer threads created 

sem_t mutex;    // semaphore for mutual exclusion
sem_t full;     // semaphore to keep track of the number of items in the buffer
sem_t empty;    // semaphore to keep track of the number of empty slots in the buffer

// The producer (add item to buffer) function  
void insert(char item)
{
    // show the item that was produced
    printf("producing letter %c ...\n", item);

    // acquire the empty semaphore (decrement its value)
    sem_wait(&empty);

    // acquire the mutex semaphore (decrement its value)
    sem_wait(&mutex);

    // add item to the bounded buffer array
    buffer[nextIn] = item;

    // increment the buffer index to the next position in the bounded buffer array
    nextIn = (nextIn + 1) % BUFF_SIZE;

    // release the mutex semaphore (increment its value)
    sem_post(&mutex);

    // release the full semaphore (increment its value)
    sem_post(&full);
}

// The producer thread that adds 10 items to buffer  
void * Produce()
{
    int i;
    printf("test 2\n");

    // call 10 instances of the insert function (the algorithm for the producer )
    for (i = 0; i < 10; i++) {
        insert('A' + i);
    }

    pthread_exit(NULL);
    return NULL;
}

// The consumer (remove an item) function
void remove_item()
{
    char item;

    // acquire the full semaphore (decrement its value)
    sem_wait(&full);

    // acquire the mutex semaphore (decrement its value)
    sem_wait(&mutex);

    // read an item from the buffer (use variable item)
    item = buffer[nextOut];

    // increment the consumer index to the next position in the buffer
    nextOut = (nextOut + 1) % BUFF_SIZE;

    // release the mutex semaphore (increment its value)
    sem_post(&mutex);

    // release the empty semaphore (increment its value)
    sem_post(&empty);

    printf("consuming letter %c ...\n", item);
}

// The consumer thread: this calls the consumer algorithm function (remove_item) 10 times 
void * Consume()
{
    int i;

    // call the consumer function the algorithm for consuming items
    for (i = 0; i < 10; i++) {
        // call the remove_item function
        remove_item();
    }

    // exit the thread gracefully
    pthread_exit(NULL);
}

// The second command line argument is the size of the bounded buffer
int main(int argc, char** argv)
{
    int buffer_size;

    pthread_t idP, idC;       // thread ID variables
    int rc1, rc2;

    times = 15;

    // check for the correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <buffer size>\n", argv[0]);
        exit(1);
    }

    // initialize the bounded buffer size
    buffer_size = atoi(argv[1]);

    // initialize the semaphores
    sem_init(&mutex, 0, 1);    // initialize mutex to 1 (binary semaphore)
    sem_init(&full, 0, 0);     // initialize full to 0 (counting semaphore)
    sem_init(&empty, 0, buffer_size);   // initialize empty to the buffer size

    if ((rc1 = pthread_create(&idP, NULL, Produce, NULL))) {
        printf("Thread creation failed: %d\n", rc1);
    }

    printf("test 1\n");

    // create thread for consumer
    if ((rc2 = pthread_create(&idC, NULL, Consume, NULL))) {
        printf("Thread creation failed: %d\n", rc2);
    }

    // synchronize worker threads and master thread (process)
    pthread_join(idP, NULL);
    pthread_join(idC, NULL);

    // destroy the semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}