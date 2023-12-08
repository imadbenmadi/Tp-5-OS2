# Producer-Consumer Problem with Semaphores

This C program illustrates a solution to the producer-consumer problem using semaphores in a Linux environment.

## Table of Contents
- [Overview](#overview)
- [Code Explanation](#code-explanation)
  - [Includes and Definitions](#includes-and-definitions)
  - [Global Variables](#global-variables)
  - [Producer Thread](#producer-thread)
  - [Consumer Thread](#consumer-thread)
  - [Main Function](#main-function)

## Overview
Tp5 of the module operation System
The producer-consumer problem is a classic synchronization issue in concurrent programming. The goal is to ensure that producers and consumers can safely share a common, fixed-size buffer.

## Code Explanation

### Includes and Definitions

```
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
```
Global Variables
```
// Semaphore for mutual exclusion.
sem_t mutex;
// Semaphore representing the number of items in the buffer.
sem_t full;
// Semaphore representing the number of available slots in the buffer.
sem_t empty;
// The shared buffer.
int buffer[BUFFER_SIZE];
// Pointers to track the position in the buffer.
int in = 0, out = 0;
```
Producer Thread
```
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
```
The producer thread continuously adds items to the buffer, ensuring synchronization with semaphores.

###Consumer Thread
```
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
```
The consumer thread continuously removes items from the buffer, ensuring synchronization with semaphores.

###Main Function
```
// Main function
int main() {
    // Initialization of semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Thread creation for producer and consumer
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish (won't happen in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

```
The main function initializes semaphores, creates threads, waits for threads to finish, and destroys semaphores.

