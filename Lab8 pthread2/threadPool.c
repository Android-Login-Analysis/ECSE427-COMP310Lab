/*
How to handle tasks in a multi threaded manner?

Have a taskqueue from where you retrieve the tasks to be executed on threads.
Have a result queue where you put the results of the tasks you executed.

FLOW:
Create a task.
Submit it to task queue.
Take the tasks from queue and assign it to a thread.
Execute the tasks on thread.
Put the result from each thread to the result queue.
Retrieve it from result queue and print the results to the user.

*/

/*
What is the computation to be executed here?

We will try to estimate the value of pi.

We iterate over a range MAX_iterations.
In each iteration, we find random x and y and then find the square of distance
of point (x,y) from origin. If the distance is less than or equal to 1 then we
increment the count of points lying within the circle. (assuming if a point lies on the circle, it lies within the circle)
We increment the count of points lying within the square in each iteration.
It is assumed that the circle centred on origin has a radius of 0.5 and the square
encompassing the circle has a side of length 1.

Value of pi will be given by - 4.0 * ((double)pCircle / (double)(pSquare))

If works because area of circle to an area of square with side 2r will be in ratio pi/4.
Provided we consider sufficiently large number of points, we can come close to the value of pi. Remember it is estimation not exact value of pi.
*/

/*
What will we do here?

Have say 10,000 iterations to be executed in total.
Break these iterations into tasks consisting of irregular number of iterations.
Add these tasks to the task queue.
Collect the sums from result queue and estimate the value of pi.
*/

/*

What is interesting about thread pool?

It prevents system from overloading.
We can limit the number of threads being launched.
Either they will be running or waiting.
The pool can be scaled up based on need.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define maxIterations 10000000
#define numThreads 10
#define taskDivisions 80

typedef struct taskDetails
{
    int iterationsProcess;
    int circles;
    int squares;
} Task;

Task taskPending[128];
double taskReturn[128];

int taskPendingCt = 0;
int taskResultCt = 0;
int threadNum = 0;
pthread_mutex_t mutexPending;
pthread_cond_t condPending;

pthread_mutex_t mutexResult;
pthread_cond_t condResult;

void addTask(Task task)
{
    // add task to pending tasks list
    pthread_mutex_lock(&mutexPending);
    taskPending[taskPendingCt] = task;
    taskPendingCt++;
    pthread_mutex_unlock(&mutexPending);
    pthread_cond_signal(&condPending);
}

void printResult(double result)
{
    // add results to results list
    // which mutex should we use here? do we need another mutex?
    //"The idea is that you have one mutex per resource whose access you want to protect independently. "
    // https://stackoverflow.com/questions/72313410/why-do-i-need-multiple-mutexes
    pthread_mutex_lock(&mutexResult);
    taskReturn[taskResultCt] = result;
    taskResultCt++;
    pthread_mutex_unlock(&mutexResult);
}

void taskProcess(Task task)
{
    // Here the task is to estimate the number of random points lying inside circle for certain iterations.
    // Radius of the circle is 1. Circle and Squares are centred on origin.
    // Side of square is 2.
    // Assume boundary of the circle is inside the circle.
    // Generate random (x,y) such that 0 <= x,y <= 1.
    task.circles = 0;
    task.squares = 0;
    double d, x, y;
    int ite = task.iterationsProcess;

    for (int i = 0; i < ite; i++)
    {
        x = (double)(rand() % (task.iterationsProcess + 1)) / task.iterationsProcess; //[0.0, 1.0]
        y = (double)(rand() % (task.iterationsProcess + 1)) / task.iterationsProcess;
        d = x * x + y * y;
        if (d <= 1)
        {
            task.circles++;
        }
        task.squares++;
    }
    double result = (4.0 * task.circles) / task.squares;
    printResult(result);
}

void *workerThread()
{
    // keep on continuing in loop
    // will make sure that threads do not terminate and exit
    while (1)
    {
        Task taskExecute;
        // enter critical section here
        pthread_mutex_lock(&mutexPending);

        while (taskPendingCt == 0)
        {
            // keep on waiting till there are no pending tasks
            // else the threads will keep on executing the code without productive output
            // fall in else branch (if present) and repeat - fill the CPU usage
            pthread_cond_wait(&condPending, &mutexPending);
        }

        // else take the first task and launch it in this thread
        taskExecute = taskPending[0];
        for (int i = 0; i < taskPendingCt - 1; i++)
        {
            taskPending[i] = taskPending[i + 1];
        }
        taskPendingCt--; // because one task will be processed now
        pthread_mutex_unlock(&mutexPending);

        if (taskExecute.iterationsProcess < 10)
        {
            // printf("treat it as our quit signal and add it back for other threads\n");
            // this will get printed before our result because we called print result after all threads shut down.
            addTask(taskExecute);
            pthread_exit(NULL);
        }

        // we are starting the work on pending task outside critical section because else it would have been serial execution for the task's work too.
        taskProcess(taskExecute);
    }
}

int main(int argc, char *argv[])
{
    pthread_t threads[numThreads];
    pthread_mutex_init(&mutexPending, NULL);
    pthread_cond_init(&condPending, NULL);

    // launch all the threads in the pool
    for (int i = 0; i < numThreads; i++)
    {
        if (pthread_create(&threads[i], NULL, &workerThread, NULL) != 0)
        {
            printf("There was an error in starting the thread.");
        }
    }

    srand(time(NULL));
    // divide the work among different tasks
    Task todo[taskDivisions];

    for (int i = 0; i < taskDivisions; i++)
    {
        if (i == taskDivisions - 1)
        {
            todo[i].iterationsProcess = maxIterations % taskDivisions + 1;
            // printf("Last task has this many iterations to process %d\n", todo[i].iterationsProcess);
            // assume we are quiting at the last thread - say when iterations to be processed are less than 10.
        }
        else
        {
            todo[i].iterationsProcess = maxIterations / numThreads;
            // printf("Thread %d has this many iterations to process %d\n", i, todo[i].iterationsProcess);
        }
        addTask(todo[i]);
    }

    // join all the threads in the pool
    for (int i = 0; i < numThreads; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("There was an error in joining the thread.");
        }
    }

    // if you want to shutdown the threadpool gracefully
    // one approach could be
    // add quit command to task queue at the end.
    // upon encountering quit, the thread will not execute the function further and return (pthread_exit(NULL)).
    // before doing this, you may want to put quit back into queue for other threads to quit as well.

    for (int i = 0; i < taskResultCt; i++)
    {
        printf("The value of pi for this division is %f - %d\n", taskReturn[i], i);
    }

    pthread_mutex_destroy(&mutexPending);
    pthread_cond_destroy(&condPending);
    return 0;
}