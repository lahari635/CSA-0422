#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    printf("Philosopher %d is thinking...\n", id);
    sleep(1);

    // Pick left chopstick
    pthread_mutex_lock(&chopstick[id]);
    printf("Philosopher %d picked left chopstick %d\n", id, id);

    // Pick right chopstick
    pthread_mutex_lock(&chopstick[(id + 1) % N]);
    printf("Philosopher %d picked right chopstick %d\n", id, (id + 1) % N);

    // Eating
    printf("Philosopher %d is eating...\n", id);
    sleep(2);

    // Put down right chopstick
    pthread_mutex_unlock(&chopstick[(id + 1) % N]);
    printf("Philosopher %d put down right chopstick %d\n", id, (id + 1) % N);

    // Put down left chopstick
    pthread_mutex_unlock(&chopstick[id]);
    printf("Philosopher %d put down left chopstick %d\n", id, id);

    printf("Philosopher %d finished eating and left.\n", id);
    return NULL;
}

int main() {
    pthread_t ph[N];
    int id[N];

    // Initialize chopsticks
    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &id[i]);
    }

    // Wait for all threads
    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    // Destroy mutexes
    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&chopstick[i]);

    return 0;
}
