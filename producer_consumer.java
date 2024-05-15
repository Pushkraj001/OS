import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class producer_consumer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get the number of items to produce and consume from the user
        System.out.print("Enter the number of items to produce and consume: ");
        int numItems = scanner.nextInt();

        Semaphore semaphoreProducer = new Semaphore(1);
        Semaphore semaphoreConsumer = new Semaphore(0);

        Producer producer = new Producer(semaphoreProducer, semaphoreConsumer, numItems);
        Consumer consumer = new Consumer(semaphoreConsumer, semaphoreProducer, numItems);

        Thread producerThread = new Thread(producer, "ProducerThread");
        Thread consumerThread = new Thread(consumer, "ConsumerThread");

        producerThread.start();
        consumerThread.start();

        scanner.close(); // Close the scanner after use
    }
}

class Producer implements Runnable {
    Semaphore semaphoreProducer;
    Semaphore semaphoreConsumer;
    int numItems;

    public Producer(Semaphore semaphoreProducer, Semaphore semaphoreConsumer, int numItems) {
        this.semaphoreProducer = semaphoreProducer;
        this.semaphoreConsumer = semaphoreConsumer;
        this.numItems = numItems;
    }

    public void run() {
        for (int i = 1; i <= numItems; i++) {
            try {
                semaphoreProducer.acquire();
                System.out.println("Produced : " + i);
                System.out.println("Consumer is waiting ");

                Thread.sleep(1000);
                semaphoreConsumer.release();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Consumer implements Runnable {
    Semaphore semaphoreConsumer;
    Semaphore semaphoreProducer;
    int numItems;

    public Consumer(Semaphore semaphoreConsumer, Semaphore semaphoreProducer, int numItems) {
        this.semaphoreConsumer = semaphoreConsumer;
        this.semaphoreProducer = semaphoreProducer;
        this.numItems = numItems;
    }

    public void run() {
        for (int i = 1; i <= numItems; i++) {
            try {
                semaphoreConsumer.acquire();
                System.out.println("Consumed : " + i);
                System.out.println("Producer is waiting ");

                Thread.sleep(1000);
                semaphoreProducer.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
