// Have three semaphores
// They can be accessed using only two functions - wait and signal/post
// •	one semaphore for counting the number of customers present in the waiting room (not including the customer in the chair)
// •	one semaphore for indicating the status of barber: working or sleeping
// •	one mutex for giving the mutual exclusion to let the processes execute

// If number of customers == number of chairs in the waiting rooms --> If new customers show up then they have to leave the shop.

// If barber is ready, customer will go and get a haircut else the customer will wait in the waiting room.
// Number of available seats in the waiting room - will decrease if more and more customers wait.

// What is the initial state?
// •	Barber is sleeping.
// •	No customer is there.
// •	All seats are available in the waiting room.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

void *barberWorker(void *idp);
void *customerWorker(void *idp);
void serve_customer();

typedef struct
{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} semaphore;

semaphore *semaphore_custom;

/* Inputs */
int countChairs;
int countCustomers;

int available_seats;
int no_served_custs = 0;
time_t waiting_time_sum;

/* Mutex */
pthread_mutex_t serveCustomer;

semaphore *semaphore_init(int value)
{
    semaphore *semaVar = malloc(sizeof(semaphore));
    semaVar->value = value;

    pthread_mutex_init(&semaVar->mutex, NULL);
    pthread_cond_init(&semaVar->cond, NULL);

    return semaVar;
}

void sem_wait(semaphore *semaVar)
{
    pthread_mutex_lock(&semaVar->mutex);
    while (semaVar->value == 0)
    {
        pthread_cond_wait(&semaVar->cond, &semaVar->mutex);
    }
    semaVar->value--;
    pthread_mutex_unlock(&semaVar->mutex);
}

void sem_post(semaphore *semaVar)
{
    pthread_mutex_lock(&semaVar->mutex);
    semaVar->value++;
    pthread_cond_broadcast(&semaVar->cond);
    pthread_mutex_unlock(&semaVar->mutex);
}

/* Semaphores */
semaphore *barber_ready;
semaphore *customer_ready;
semaphore *modifySeats;

void *barberWorker(void *idp)
{
    int counter = 0;

    while (1)
    {
        /* Lock semaphore "customer_ready" - try to get a customer or sleep if there is none */
        /* Barber sleeps when there is no customer */
        sem_wait(customer_ready);

        /* Lock semaphore "modifySeats" - try to get access to seats */
        sem_wait(modifySeats);

        /* Increment by 1 the available seats */
        available_seats++;

        /* Unlock semaphore "modifySeats" */
        sem_post(modifySeats);

        /* Unlock semaphore "barber_ready" - set barber ready to serve */
        sem_post(barber_ready);

        /* Lock mutex "srvCust" - protect service by the same barber from other threads */
        pthread_mutex_lock(&serveCustomer);

        /* Serve customer */
        /* Keep this in a critical section */
        serve_customer();

        /* Unlock mutex "srvCust" - finished service */
        pthread_mutex_unlock(&serveCustomer);

        printf("Customer was served.\n");

        counter++;
        if (counter == (countCustomers - no_served_custs))
            break;
    }
    pthread_exit(NULL);
}

void *customerWorker(void *idp)
{
    struct timeval start, stop;

    /* Lock semaphore "modifySeats" */
    sem_wait(modifySeats);

    /* If there is available seat */
    if (available_seats >= 1)
    {
        /* Occupy a seat */
        available_seats--;

        printf("Customer[pid = %lu] is waiting.\n", pthread_self());
        printf("Available seats: %d\n", available_seats);

        /* Start waiting-time counter */
        gettimeofday(&start, NULL);

        /* Unlock semaphore "customer_ready" - set the customer ready to be served */
        sem_post(customer_ready);

        /* Unlock semaphore "modifySeats" */
        sem_post(modifySeats);

        /* Lock semaphore "barber_ready" - wait for barber to get ready */
        sem_wait(barber_ready);

        /* Stop waiting-time counter */
        gettimeofday(&stop, NULL);

        double sec = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

        /* Assign the time spent to global variable (ms) */
        waiting_time_sum += 1000 * sec;
        printf("Customer[pid = %lu] is being served. \n", pthread_self());
    }
    else
    {
        /* Unlock semaphore "modifySeats" */
        sem_post(modifySeats);
        no_served_custs++;
        printf("A Customer left.\n");
    }

    pthread_exit(NULL);
}

void serve_customer()
{
    /* Some calculation to simulate work being done by the barber - hair cutting */
    /* Random number between 0 and 400 (miliseconds) */
    int s = rand() % 401;

    /* Convert miliseconds to microseconds */
    s = s * 1000;
    usleep(s);
}

int main()
{
    srand(time(NULL));

    printf("Please enter the number of seats: \n");
    scanf("%d", &countChairs);

    printf("Please enter the total customers: \n");
    scanf("%d", &countCustomers);

    available_seats = countChairs;

    // threads for barber and customer
    pthread_t barber_1;
    pthread_t customers[countCustomers];

    /* Initialize mutex */
    pthread_mutex_init(&serveCustomer, NULL);

    /* Initialize semaphores */
    customer_ready = semaphore_init(0);
    barber_ready = semaphore_init(0);
    modifySeats = semaphore_init(1); // note that the count is 1

    // create barber and customer threads.
    if (pthread_create(&barber_1, NULL, (void *)barberWorker, NULL) != 0)
    {
        printf("Failed to create barber thread.");
    }

    for (int i = 0; i < countCustomers; i++)
    {
        if (pthread_create(&customers[i], NULL, (void *)customerWorker, NULL) != 0)
        {
            printf("There was an error in creating customer thread.");
        }
        /* Sleep for 100ms before creating another customer */
        usleep(100000);
    }

    /* Wait for threads to finish */
    pthread_join(barber_1, NULL);

    for (int i = 0; i < countCustomers; i++)
    {
        if (pthread_join(customers[i], NULL) != 0)
        {
            printf("Could not join customer threads.");
        }
    }

    printf("\n------------------------------------------------\n");
    printf("Average customers' waiting time: %f ms.\n", (waiting_time_sum / (double)(countCustomers - no_served_custs)));
    printf("Number of customers that were forced to leave: %d\n", no_served_custs);
}