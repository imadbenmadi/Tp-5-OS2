# Tp-5-OS2
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
- [Building and Running](#building-and-running)
- [Resources](#resources)

## Overview

The producer-consumer problem is a classic synchronization issue in concurrent programming. The goal is to ensure that producers and consumers can safely share a common, fixed-size buffer.

## Code Explanation

### Includes and Definitions

The necessary header files and definitions are included.

### Global Variables

- `mutex`: Semaphore for mutual exclusion.
- `full`: Semaphore representing the number of items in the buffer.
- `empty`: Semaphore representing the number of available slots in the buffer.
- `buffer`: The shared buffer.
- `in` and `out`: Pointers to track the position in the buffer.

### Producer Thread

The producer thread continuously adds items to the buffer, ensuring synchronization with semaphores.

### Consumer Thread

The consumer thread continuously removes items from the buffer, ensuring synchronization with semaphores.

### Main Function

- Initializes semaphores.
- Creates threads for the producer and consumer.
- Waits for threads to finish (won't happen in this example).
- Destroys semaphores.

## Building and Running

Ensure you have a Linux environment with a C compiler. You can compile the program using the following commands:

```bash
gcc -pthread filename.c -o producer_consumer
./producer_consumer
