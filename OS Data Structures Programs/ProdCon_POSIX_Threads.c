/*

    This program creates two threads: a producer and a consumer. The producer generates random items and inserts them into the buffer, while the consumer removes items from the buffer and consumes them. The buffer is protected by a mutex semaphore, and there are two counting semaphores: one to keep track of the number of empty slots in the buffer, and one to keep track of the number of full slots. 

    The producer waits on the empty_count semaphore (which is initialized to the buffer size) before inserting an item into the buffer. It also waits on the buffer_mutex semaphore to ensure mutual exclusion when accessing the buffer. After inserting an item, it signals the full_count semaphore to indicate that a slot in the buffer is now full.

    The consumer waits on the full_count semaphore before removing an item from the buffer. It also waits on the buffer_mutex semaphore for mutual exclusion. After removing an item, it signals the empty_count semaphore to indicate that a slot in the buffer is now empty.

    Note that this code assumes that the buffer is large enough to hold all items produced before they are consumed. If the buffer is full and the producer tries to insert an item, it will block on the empty_count semaphore until a slot becomes available. Similarly, if the buffer is empty and the consumer tries to remove an item, it will block on the full_count semaphore until a slot becomes full.

    Output: Never ending loop

    Produced item 1586963286
    Produced item 460017635
    Produced item 1944388166
    Produced item 551484640
    Produced item 1758725001
    Produced item 1255266716
    Produced item 630043976
    Produced item 1089075823
    Consumed item 6146446
    Consumed item 1089075823
    Consumed item 238516416
    Consumed item 630043976
    Consumed item 1255266716
    Consumed item 1758725001
    Consumed item 551484640
    Consumed item 1944388166
    Consumed item 460017635
    Consumed item 1586963286
    Consumed item 186236468
    Consumed item 899485792
    Produced item 238516416
    Produced item 1869940541
    Produced item 583721187
    Produced item 1432951810
    ...

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int buffer_index;
sem_t buffer_mutex, empty_count, full_count;

void insert(int item) {
    buffer[buffer_index++] = item;
}

int remove_item() {
    return buffer[--buffer_index];
}

void *producer(void *arg) {
    int item = 0;
    while (1) {
        item = rand(); // Generate a random item
        sem_wait(&empty_count);
        sem_wait(&buffer_mutex);
        insert(item);
        sem_post(&buffer_mutex);
        sem_post(&full_count);
        printf("Produced item %d\n", item);
    }
}

void *consumer(void *arg) {
    int item = 0;
    while (1) {
        sem_wait(&full_count);
        sem_wait(&buffer_mutex);
        item = remove_item();
        sem_post(&buffer_mutex);
        sem_post(&empty_count);
        printf("Consumed item %d\n", item);
    }
}

int main(int argc, char **argv) {
    buffer_index = 0;
    sem_init(&buffer_mutex, 0, 1);
    sem_init(&empty_count, 0, BUFFER_SIZE);
    sem_init(&full_count, 0, 0);
    
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    sem_destroy(&buffer_mutex);
    sem_destroy(&empty_count);
    sem_destroy(&full_count);
    
    return 0;
}