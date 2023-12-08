#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t mutex, full, empty;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Producer thread function
void *producer(void *arg) {
    int item = 1; // item to be produced

    while (1) {
        sem_wait(&empty); // Wait if buffer is full
        sem_wait(&mutex); // Enter critical section

        // Critical Section: Add item to buffer
        buffer[in] = item;
        printf("Produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Exit critical section
        sem_post(&full);  // Signal that an item has been produced
    }
}

// Consumer thread function
void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);  // Wait if buffer is empty
        sem_wait(&mutex); // Enter critical section

        // Critical Section: Remove item from buffer
        int item = buffer[out];
        printf("Consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal that a slot in the buffer is empty
    }
}

int main() {
    // Initialization of semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Thread creation for producer and consumer
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish 
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
