#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class monitor {
private:
    int rcnt, wcnt, waitr, waitw;
    pthread_cond_t canread, canwrite;
    pthread_mutex_t condlock;

public:
    monitor() {
        rcnt = wcnt = waitr = waitw = 0;
        pthread_cond_init(&canread, NULL);
        pthread_cond_init(&canwrite, NULL);
        pthread_mutex_init(&condlock, NULL);
    }

    void beginread(int i) {
        pthread_mutex_lock(&condlock);
        if (wcnt || waitw) {
            waitr++;
            pthread_cond_wait(&canread, &condlock);
            waitr--;
        }
        rcnt++;
        cout << "reader " << i << " is reading\n";
        pthread_mutex_unlock(&condlock);
        pthread_cond_broadcast(&canread);
    }

    void endread(int i) {
        pthread_mutex_lock(&condlock);
        if (--rcnt == 0)
            pthread_cond_signal(&canwrite);
        pthread_mutex_unlock(&condlock);
    }

    void beginwrite(int i) {
        pthread_mutex_lock(&condlock);
        if (wcnt || rcnt) {
            ++waitw;
            pthread_cond_wait(&canwrite, &condlock);
            --waitw;
        }
        wcnt = 1;
        cout << "writer " << i << " is writing\n";
        pthread_mutex_unlock(&condlock);
    }

    void endwrite(int i) {
        pthread_mutex_lock(&condlock);
        wcnt = 0;
        if (waitr)
            pthread_cond_signal(&canread);
        else
            pthread_cond_signal(&canwrite);
        pthread_mutex_unlock(&condlock);
    }
};

monitor M;

void* reader(void* id) {
    int c = 0, i = *(int*)id;
    while (c++ < 5) {
        usleep(1);
        M.beginread(i);
        M.endread(i);
    }
}

void* writer(void* id) {
    int c = 0, i = *(int*)id;
    while (c++ < 5) {
        usleep(1);
        M.beginwrite(i);
        M.endwrite(i);
    }
}

int main() {
    pthread_t r[5], w[5];
    int id[5];
    for (int i = 0; i < 5; i++) {
        id[i] = i;
        pthread_create(&r[i], NULL, &reader, &id[i]);
        pthread_create(&w[i], NULL, &writer, &id[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }
}
