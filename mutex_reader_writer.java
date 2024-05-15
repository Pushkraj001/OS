import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Monitor {
    private int rcnt, wcnt, waitr, waitw;
    private final Lock lock = new ReentrantLock();
    private final Condition canRead = lock.newCondition();
    private final Condition canWrite = lock.newCondition();

    Monitor() {
        rcnt = wcnt = waitr = waitw = 0;
    }

    void beginRead(int i) throws InterruptedException {
        lock.lock();
        try {
            while (wcnt > 0 || waitw > 0) {
                waitr++;
                canRead.await();
                waitr--;
            }
            rcnt++;
            System.out.println("reader " + i + " is reading");
            canRead.signalAll();
        } finally {
            lock.unlock();
        }
    }

    void endRead(int i) {
        lock.lock();
        try {
            if (--rcnt == 0)
                canWrite.signal();
        } finally {
            lock.unlock();
        }
    }

    void beginWrite(int i) throws InterruptedException {
        lock.lock();
        try {
            while (wcnt > 0 || rcnt > 0) {
                waitw++;
                canWrite.await();
                waitw--;
            }
            wcnt = 1;
            System.out.println("writer " + i + " is writing");
        } finally {
            lock.unlock();
        }
    }

    void endWrite(int i) {
        lock.lock();
        try {
            wcnt = 0;
            if (waitr > 0)
                canRead.signal();
            else
                canWrite.signal();
        } finally {
            lock.unlock();
        }
    }
}

public class mutex_reader_writer {
    static Monitor M = new Monitor();

    static class Reader implements Runnable {
        private final int id;

        Reader(int id) {
            this.id = id;
        }

        public void run() {
            int c = 0;
            while (c++ < 5) {
                try {
                    Thread.sleep(1);
                    M.beginRead(id);
                    M.endRead(id);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class Writer implements Runnable {
        private final int id;

        Writer(int id) {
            this.id = id;
        }

        public void run() {
            int c = 0;
            while (c++ < 5) {
                try {
                    Thread.sleep(1);
                    M.beginWrite(id);
                    M.endWrite(id);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        Thread[] r = new Thread[5];
        Thread[] w = new Thread[5];

        for (int i = 0; i < 5; i++) {
            r[i] = new Thread(new Reader(i));
            w[i] = new Thread(new Writer(i));
            r[i].start();
            w[i].start();
        }

        try {
            for (int i = 0; i < 5; i++) {
                r[i].join();
                w[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
