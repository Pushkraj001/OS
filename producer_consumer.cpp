#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphoreProducer;
sem_t semaphoreConsumer;

class Producer {
public:
    Producer(sem_t &semProducer, sem_t &semConsumer, int numIterations) : semaphoreProducer(semProducer), semaphoreConsumer(semConsumer), iterations(numIterations) {}

    void operator()() {
        for (int i = 1; i <= iterations; i++) {
            sem_wait(&semaphoreProducer);
            std::cout << "Produced : " << i << std::endl;
            std::cout << "Consumer is waiting" << std::endl;
            sleep(1);
            sem_post(&semaphoreConsumer);
        }
    }

private:
    sem_t &semaphoreProducer;
    sem_t &semaphoreConsumer;
    int iterations;
};

class Consumer {
public:
    Consumer(sem_t &semConsumer, sem_t &semProducer, int numIterations) : semaphoreConsumer(semConsumer), semaphoreProducer(semProducer), iterations(numIterations) {}

    void operator()() {
        for (int i = 1; i <= iterations; i++) {
            sem_wait(&semaphoreConsumer);
            std::cout << "Consumed : " << i << std::endl;
            std::cout << "Producer is waiting" << std::endl;
            sleep(1);
            sem_post(&semaphoreProducer);
        }
    }

private:
    sem_t &semaphoreConsumer;
    sem_t &semaphoreProducer;
    int iterations;
};

int main() {
    int numIterations;
    std::cout << "Enter the number of iterations: ";
    std::cin >> numIterations;

    sem_init(&semaphoreProducer, 0, 1);
    sem_init(&semaphoreConsumer, 0, 0);

    Producer producer(semaphoreProducer, semaphoreConsumer, numIterations);
    Consumer consumer(semaphoreConsumer, semaphoreProducer, numIterations);

    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    sem_destroy(&semaphoreProducer);
    sem_destroy(&semaphoreConsumer);

    return 0;
}
