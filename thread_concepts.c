// thread_concepts.c
// Demonstrate pthread_create, pthread_join, pthread_equal, pthread_exit

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *arg) {
    pthread_t self = pthread_self();
    printf("Worker thread started (tid=%lu)\n", (unsigned long)self);
    sleep(1);
    if (pthread_equal(self, pthread_self())) printf("pthread_equal true for self\n");
    pthread_exit((void*)42);
}

int main() {
    pthread_t t;
    void *ret;
    pthread_create(&t, NULL, worker, NULL);
    printf("Main: created thread tid=%lu\n", (unsigned long)t);
    pthread_join(t, &ret);
    printf("Thread joined, return value = %ld\n", (long)ret);
    return 0;
}
