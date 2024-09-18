// Exercise: Deadlock
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock1, lock2;

void *resource1(void *arg)
{
    pthread_mutex_lock(&lock1);
    printf("Thread 1: Locked resource 1\n");
    sleep(1); // Sleep to ensure Thread 2 locks resource 2

    pthread_mutex_lock(&lock2);
    printf("Thread 1: Locked resource 2\n");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("Thread 1: Unlocked resources 1 and 2\n");
    return NULL;
}

void *resource2(void *arg)
{
    pthread_mutex_lock(&lock2);
    printf("Thread 2: Locked resource 2\n");
    sleep(1); // Sleep to ensure Thread 1 locks resource 1

    pthread_mutex_lock(&lock1);
    printf("Thread 2: Locked resource 1\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    printf("Thread 2: Unlocked resources 1 and 2\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, resource1, NULL);
    pthread_create(&t2, NULL, resource2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}
