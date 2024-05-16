#include <iostream>
#include <thread>
#include <semaphore.h> // For semaphore functionality
#include <unistd.h> // For sleep function

// Semaphore declarations
sem_t semaphoreProducer;
sem_t semaphoreConsumer;

// Producer class definition
class Producer {
public:
    // Constructor
    Producer(sem_t &semProducer, sem_t &semConsumer, int numIterations) : semaphoreProducer(semProducer), semaphoreConsumer(semConsumer), iterations(numIterations) {}

    // Overloaded function call operator
    void operator()() {
        // Loop for producing items
        for (int i = 1; i <= iterations; i++) {
            sem_wait(&semaphoreProducer); // Wait for producer semaphore
            std::cout << "Produced: " << i << std::endl; // Print produced item
            std::cout << "Consumer is waiting" << std::endl; // Indicate consumer is waiting
            sleep(1); // Simulate processing time
            sem_post(&semaphoreConsumer); // Signal consumer semaphore
        }
    }

private:
    sem_t &semaphoreProducer; // Reference to producer semaphore
    sem_t &semaphoreConsumer; // Reference to consumer semaphore
    int iterations; // Number of iterations
};

// Consumer class definition
class Consumer {
public:
    // Constructor
    Consumer(sem_t &semConsumer, sem_t &semProducer, int numIterations) : semaphoreConsumer(semConsumer), semaphoreProducer(semProducer), iterations(numIterations) {}

    // Overloaded function call operator
    void operator()() {
        // Loop for consuming items
        for (int i = 1; i <= iterations; i++) {
            sem_wait(&semaphoreConsumer); // Wait for consumer semaphore
            std::cout << "Consumed: " << i << std::endl; // Print consumed item
            std::cout << "Producer is waiting" << std::endl; // Indicate producer is waiting
            sleep(1); // Simulate processing time
            sem_post(&semaphoreProducer); // Signal producer semaphore
        }
    }

private:
    sem_t &semaphoreConsumer; // Reference to consumer semaphore
    sem_t &semaphoreProducer; // Reference to producer semaphore
    int iterations; // Number of iterations
};

int main() {
    int numIterations;
    std::cout << "Enter the number of iterations: ";
    std::cin >> numIterations;

    // Initialize semaphores
    sem_init(&semaphoreProducer, 0, 1);
    sem_init(&semaphoreConsumer, 0, 0);

    // Create instances of Producer and Consumer classes
    Producer producer(semaphoreProducer, semaphoreConsumer, numIterations);
    Consumer consumer(semaphoreConsumer, semaphoreProducer, numIterations);

    // Create threads for producer and consumer
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    // Join threads
    producerThread.join();
    consumerThread.join();

    // Destroy semaphores
    sem_destroy(&semaphoreProducer);
    sem_destroy(&semaphoreConsumer);

    return 0;
}
