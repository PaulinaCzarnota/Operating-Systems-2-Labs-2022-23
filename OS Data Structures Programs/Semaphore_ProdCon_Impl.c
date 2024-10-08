/*

    In this implementation, we use three semaphores: empty, full, and mutex. The empty semaphore represents the number of empty slots in the buffer, the full semaphore represents the number of full slots in the buffer, and the mutex semaphore is used to ensure mutual exclusion when accessing the buffer.

    The producer thread generates a random item and adds it to the buffer. It waits for an empty slot in the buffer by decrementing the empty semaphore, and once it acquires the lock on the buffer by decrementing the mutex semaphore, it adds the item to the buffer, updates the index, and releases the lock by incrementing the mutex semaphore. It then signals that the buffer is not empty by incrementing the full semaphore, and waits for a bit before producing the next item.

    The consumer thread retrieves an item from the buffer and consumes it. It waits for a non-empty buffer by decrementing the full semaphore, and once it acquires the lock on the buffer by decrementing the mutex semaphore, it retrieves an item from the buffer, updates the index, and releases the lock by incrementing the mutex semaphore. It then signals that the buffer is not full by incrementing the empty semaphore, and waits for a bit before consuming the next item.

    The main function initializes the semaphores, creates the producer and consumer threads, waits for the threads to finish, and destroys the semaphores.

    Overall, this implementation ensures that the producer and consumer threads do not access the buffer at the same time, and that the buffer is not accessed when it is full or empty. This helps prevent race conditions and ensures that the producer-consumer problem is solved correctly.

    Output:

    Producer produced item 83 at index 0
    Consumer consumed item 83 from index 0
    Producer produced item 86 at index 1
    Consumer consumed item 86 from index 1
    Producer produced item 77 at index 2
    Producer produced item 15 at index 3
    Consumer consumed item 77 from index 2
    Producer produced item 93 at index 4
    Producer produced item 35 at index 0
    Consumer consumed item 15 from index 3
    Producer produced item 86 at index 1
    Producer produced item 92 at index 2
    Consumer consumed item 93 from index 4
    Producer produced item 49 at index 3
    Producer produced item 21 at index 4
    Consumer consumed item 35 from index 0
    Consumer consumed item 86 from index 1
    Consumer consumed item 92 from index 2
    Consumer consumed item 49 from index 3
    Consumer consumed item 21 from index 4

*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    int item, i;
    for (i = 0; i < 10; i++) {
        item = rand() % 100; // generate a random item to produce
        sem_wait(&empty); // wait for an empty slot in the buffer
        sem_wait(&mutex); // acquire the lock on the buffer
        buffer[in] = item; // add the item to the buffer
        printf("Producer produced item %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // update the index
        sem_post(&mutex); // release the lock on the buffer
        sem_post(&full); // signal that the buffer is not empty
        sleep(1); // wait for a bit before producing the next item
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item, i;
    for (i = 0; i < 10; i++) {
        sem_wait(&full); // wait for a non-empty buffer
        sem_wait(&mutex); // acquire the lock on the buffer
        item = buffer[out]; // retrieve an item from the buffer
        printf("Consumer consumed item %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // update the index
        sem_post(&mutex); // release the lock on the buffer
        sem_post(&empty); // signal that the buffer is not full
        sleep(2); // wait for a bit before consuming the next item
    }
    pthread_exit(NULL);
}

int main() {
    // initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // create the producer and consumer threads
    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // wait for the threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // destroy the semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}