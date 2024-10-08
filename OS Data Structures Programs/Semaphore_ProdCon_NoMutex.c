/*

In both examples, the producer thread produces items and puts them into the buffer, while the consumer thread consumes items from the buffer. The empty semaphore is used to keep track of the number of empty slots in the buffer, while the full semaphore is used to keep track of the number of full slots in the buffer. In the second example, a mutex is used to ensure that only one thread can access the buffer at a time.

*/

/*
    Both codes ouput:
    
    Producer produced item 1
    Consumer consumed item 1
    Producer produced item 2
    Consumer consumed item 2
    Producer produced item 3
    Consumer consumed item 3
    Producer produced item 4
    Consumer consumed item 4
    Producer produced item 5
    Consumer consumed item 5
    Producer produced item 6
    Consumer consumed item 6
    Producer produced item 7
    Consumer consumed item 7
    Producer produced item 8
    Consumer consumed item 8
    Producer produced item 9
    Consumer consumed item 9
    Producer produced item 10
    Consumer consumed item 10
    Producer produced item 11
    Consumer consumed item 11
    Producer produced item 12
    Consumer consumed item 12
    Producer produced item 13
    Consumer consumed item 13
    Producer produced item 14
    ...

*/


// Semaphore example without mutex

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        item++;
        sem_wait(&empty);
        buffer[in] = item;
        printf("Producer produced item %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&full);
        usleep(1000000); // sleep for 1 second
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);
        item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&empty);
        usleep(500000); // sleep for 0.5 seconds
    }
}

int main(int argc, char *argv[]) {
    pthread_t prod_tid, cons_tid;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


// Semaphore example with mutex for producer-consumer problem

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        item++;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer produced item %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep(1000000); // sleep for 1 second
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(500000); // sleep for 0.5 seconds
    }
}

int main(int argc, char *argv[]) {
    pthread_t prod_tid, cons_tid;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}