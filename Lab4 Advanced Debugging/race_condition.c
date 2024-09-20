#include <pthread.h>
#include <stdio.h>

/*
atomic_int counter = 0;

void increment() {
    atomic_fetch_add(&counter, 1);  // Atomically increments 'counter' by 1
}
*/

int shared_var = 0;

void *increment(void *arg)
{
    shared_var++;
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Final value: %d\n", shared_var);
    return 0;
}
