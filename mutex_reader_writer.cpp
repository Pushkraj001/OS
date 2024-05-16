#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// Monitor class definition
class Monitor {
private:
    int readerCount, writerCount, waitingReaders, waitingWriters;
    pthread_cond_t canRead, canWrite;
    pthread_mutex_t conditionLock;

public:
    // Constructor to initialize member variables and synchronization primitives
    Monitor() {
        readerCount = writerCount = waitingReaders = waitingWriters = 0;
        pthread_cond_init(&canRead, NULL); // Initialize condition variable for readers
        pthread_cond_init(&canWrite, NULL); // Initialize condition variable for writers
        pthread_mutex_init(&conditionLock, NULL); // Initialize mutex lock
    }

    // Method for readers to begin reading
    void beginRead(int i) {
        pthread_mutex_lock(&conditionLock); // Acquire mutex lock
        // Check if there are active writers or writers waiting
        if (writerCount || waitingWriters) {
            waitingReaders++; // Increment count of waiting readers
            pthread_cond_wait(&canRead, &conditionLock); // Wait for signal to read
            waitingReaders--; // Decrement count of waiting readers after waking up
        }
        readerCount++; // Increment count of active readers
        cout << "Reader " << i << " is reading" << endl; // Print message indicating reader is reading
        pthread_mutex_unlock(&conditionLock); // Release mutex lock
        pthread_cond_broadcast(&canRead); // Broadcast signal to other readers
    }

    // Method for readers to end reading
    void endRead(int i) {
        pthread_mutex_lock(&conditionLock); // Acquire mutex lock
        if (--readerCount == 0) // If no more active readers
            pthread_cond_signal(&canWrite); // Signal waiting writers
        pthread_mutex_unlock(&conditionLock); // Release mutex lock
    }

    // Method for writers to begin writing
    void beginWrite(int i) {
        pthread_mutex_lock(&conditionLock); // Acquire mutex lock
        // Check if there are active readers or writers
        if (writerCount || readerCount) {
            waitingWriters++; // Increment count of waiting writers
            pthread_cond_wait(&canWrite, &conditionLock); // Wait for signal to write
            waitingWriters--; // Decrement count of waiting writers after waking up
        }
        writerCount = 1; // Set writer count to indicate writer is active
        cout << "Writer " << i << " is writing" << endl; // Print message indicating writer is writing
        pthread_mutex_unlock(&conditionLock); // Release mutex lock
    }

    // Method for writers to end writing
    void endWrite(int i) {
        pthread_mutex_lock(&conditionLock); // Acquire mutex lock
        writerCount = 0; // Reset writer count to indicate writer has finished writing
        if (waitingReaders) // If there are waiting readers
            pthread_cond_signal(&canRead); // Signal waiting readers
        else
            pthread_cond_signal(&canWrite); // Signal waiting writers
        pthread_mutex_unlock(&conditionLock); // Release mutex lock
    }
};

Monitor M; // Declare Monitor object for synchronization

// Reader thread function
void* reader(void* id) {
    int count = 0, i = *(int*)id; // Initialize variables for loop count and reader ID
    while (count++ < 5) { // Repeat reading process 5 times
        usleep(1); // Sleep for a short period to simulate processing time
        M.beginRead(i); // Call beginRead method of Monitor to start reading
        M.endRead(i); // Call endRead method of Monitor to finish reading
    }
}

// Writer thread function
void* writer(void* id) {
    int count = 0, i = *(int*)id; // Initialize variables for loop count and writer ID
    while (count++ < 5) { // Repeat writing process 5 times
        usleep(1); // Sleep for a short period to simulate processing time
        M.beginWrite(i); // Call beginWrite method of Monitor to start writing
        M.endWrite(i); // Call endWrite method of Monitor to finish writing
    }
}

int main() {
    pthread_t readerThreads[5], writerThreads[5]; // Declare arrays for reader and writer threads
    int id[5]; // Declare array for thread IDs
    for (int i = 0; i < 5; i++) { // Loop to create reader and writer threads
        id[i] = i; // Assign ID to each thread
        pthread_create(&readerThreads[i], NULL, &reader, &id[i]); // Create reader thread
        pthread_create(&writerThreads[i], NULL, &writer, &id[i]); // Create writer thread
    }
    for (int i = 0; i < 5; i++) { // Loop to join reader and writer threads
        pthread_join(readerThreads[i], NULL); // Join reader thread
        pthread_join(writerThreads[i], NULL); // Join writer thread
    }
    return 0; // Exit program
}
