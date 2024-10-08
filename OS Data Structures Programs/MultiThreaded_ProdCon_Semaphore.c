/*

This is a multi-threaded program that implements a producer-consumer problem using semaphores and a mutex lock to synchronize access to a shared buffer.

The program defines a buffer_item type which is used for the items stored in the shared buffer. The buffer has a fixed size of 5, which is defined by the BUFFER_SIZE macro.

The program creates two semaphores, one for empty slots in the buffer (empty) and one for full slots in the buffer (full), and initializes them accordingly. It also creates a mutex lock (mutex) to synchronize access to the buffer.

The program defines two functions, insert_item() and remove_item(), which respectively insert and remove items from the buffer. These functions are called by the producer and consumer threads, which are created by the program.

The producer threads run a loop where they sleep for a random amount of time between 1 and 4 seconds, generate a random item, acquire the empty semaphore, lock the mutex, insert the item into the buffer, unlock the mutex, and increment the full semaphore.

The consumer threads run a similar loop where they sleep for a random amount of time, acquire the full semaphore, lock the mutex, remove an item from the buffer, unlock the mutex, and increment the empty semaphore.

The main function of the program takes three integer arguments from the command line: the duration of the program in seconds, the number of producer threads to create, and the number of consumer threads to create. The program creates the specified number of producer and consumer threads, runs for the specified duration, and then exits.

Output:

paulina-czarnota@LAPTOP-0IOQHBSN:~$ gcc vb.c -pthread -lrt -o vb
paulina-czarnota@LAPTOP-0IOQHBSN:~$ ./vb 30 2 2


Producer inserted item 1957747793.
Consumer removed item 1957747793.
Producer inserted item 1649760492.
Consumer removed item 1649760492.
Producer inserted item 1025202362.
Consumer removed item 1025202362.
Producer inserted item 1102520059.
Consumer removed item 1102520059.
Producer inserted item 1365180540.
Consumer removed item 1365180540.
Producer inserted item 1303455736.
Consumer removed item 1303455736.
Producer inserted item 294702567.
Consumer removed item 294702567.
Producer inserted item 861021530.
Producer inserted item 278722862.
Consumer removed item 278722862.
Consumer removed item 861021530.
Producer inserted item 1801979802.
Consumer removed item 1801979802.
Producer inserted item 1315634022.
Consumer removed item 1315634022.
Producer inserted item 2089018456.
Consumer removed item 2089018456.
Producer inserted item 1131176229.
Consumer removed item 1131176229.
Producer inserted item 1914544919.
Consumer removed item 1914544919.
Producer inserted item 1734575198.
Consumer removed item 1734575198.
Producer inserted item 2038664370.
Producer inserted item 184803526.
Consumer removed item 184803526.
Producer inserted item 1911759956.
Consumer removed item 1911759956.
Producer & consumer demo complete.

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef int buffer_item;

#define BUFFER_SIZE 5
#define TRUE 1


// The circular buffer
buffer_item buffer[BUFFER_SIZE];

// Global variable for the buffer counter
int counter;

// Semaphore for number of empty slots in the buffer
sem_t empty;

// Semaphore for number of full slots in the buffer
sem_t full;

// Mutual exclusion lock
pthread_mutex_t mutex;


// Inserts an item into the buffer
// Returns 0 if successful, otherwise -1 indicating an error occurred
int insert_item(buffer_item item) {

    if (counter < BUFFER_SIZE) {
        buffer[counter] = item;
        counter++;
        return 0;
    }
    return -1;
}

// Removes an object from the buffer, placing it in `item`
// Returns 0 if successful, otherwise -1 indicating an error occurred
int remove_item(buffer_item *item) {

    if (counter > 0) {
        *item = buffer[--counter];
        return 0;
    }
    return -1;
}

// Producer thread
void* producer(void *param) {

    buffer_item item;

    while (TRUE) {

        // Sleep for a random amount of time between 1 and 4 seconds
        sleep(rand() % 4 + 1);

        // Create the item to be inserted
        item = rand();

        // Decrement the empty semaphore
        sem_wait(&empty);

        // Acquire mutex lock before critical section
        pthread_mutex_lock(&mutex);

        // Critical section, insert the item into buffer
        if (insert_item(item) == 0) {
            printf("Producer inserted item %d.\n", item);
        } else {
            printf("Producer error.\n");
        }

        // Critical section finished, release the mutex lock
        pthread_mutex_unlock(&mutex);

        // Increment the full semaphore, signalling that consumer process may start
        sem_post(&full);
    }
}

// Consumer thread
void* consumer(void *param) {

    buffer_item item;

    while (TRUE) {

        // Sleep for a random amount of time between 1 and 4 seconds
        sleep(rand() % 4 + 1);

        // Decrement the full semaphore
        sem_wait(&full);

        // Acquire mutex lock before critical section
        pthread_mutex_lock(&mutex);

        // Critical section, insert the item into buffer
        if (remove_item(&item) == 0) {
            printf("Consumer removed item %d.\n", item);
        } else {
            printf("Consumer error.\n");
        }

        // Critical section finished, release the mutex lock
        pthread_mutex_unlock(&mutex);

        // Increment the empty semaphore, signalling that producer process may start
        sem_post(&empty);
    }
}

// Initializes the semaphores and mutex lock
void init_locks() {

    // Initialize mutex lock
    pthread_mutex_init(&mutex, NULL);

    // Initialize full semaphore to 0 and empty semaphore to BUFFER_SIZE
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
}

int main(int argc, char* argv[]) {

    // Check correct number of arguments passed by command line
    if (argc != 4) {
        printf("Error: Incorrect number of arguments.\n");
        return -1;
    }

    // Get parameters
    int sleep_duration = atoi(argv[1]);
    int num_producer_threads = atoi(argv[2]);
    int num_consumer_threads = atoi(argv[3]);

    // Initialize buffer
    counter = 0;

    // Initialize semaphores and mutex lock
    init_locks();

    // Create producer and consumer threads
    int i=0;
    pthread_t thread_id;

    for (i=0; i<num_producer_threads; i++) {
        pthread_create(&thread_id, NULL, producer, NULL);
    }

    for (i=0; i<num_consumer_threads; i++) {
        pthread_create(&thread_id, NULL, consumer, NULL);
    }

    // Main program - how long to run before terminating
    sleep(sleep_duration);

    // Exit program
    printf("Producer & consumer demo complete.\n\n");
    exit(0);
    return 0;
}