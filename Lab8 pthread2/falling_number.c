#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <ncurses.h>

#define GAP 15000

int x_bound, y_bound;
pthread_mutex_t mutexFalling;

void *workerTask(void *args)
{
    // generate any random digit to print on screen
    int digit = rand() % 10;

    // start y coordinate from top but vary x randomly
    int x = rand() % x_bound;
    int y = 0;
    int delay = rand() % 80 + 60;

    while (y < y_bound)
    { // keep on printing to show as if number is falling down.
        // set the color properties to the current window
        attron(COLOR_PAIR(1));

        // we will print digits and spaces in critical section separately
        pthread_mutex_lock(&mutexFalling);
        mvprintw(y, x, "%d", digit); // move cursor to a particular position and then print
        refresh();                   // tell curses to redraw the screen
        pthread_mutex_unlock(&mutexFalling);
        attroff(COLOR_PAIR(1));
        usleep((GAP * delay) / y_bound);

        pthread_mutex_lock(&mutexFalling);
        mvprintw(y++, x, " ");
        refresh();
        pthread_mutex_unlock(&mutexFalling);
    }
}

int main()
{
    srand(time(NULL)); // initialise random seed using clock.
    initscr();         // to initialize the ncurses data structures and to read the proper terminfo file.
    noecho();          // disable echo mode for current screen.
    curs_set(0);       // sets the appearance of the cursor based on the value of visibility - 0 means invisible
    start_color();     // do this to use color output

    init_pair(1, COLOR_BLUE, COLOR_BLACK); // initialise the pair of colors for output
    y_bound = getmaxy(stdscr);             // get an idea of windows dimensions
    x_bound = getmaxx(stdscr);             // get an idea of windows dimensions
    // https://stackoverflow.com/questions/42239726/how-does-getmaxyx-work-from-curses

    pthread_mutex_init(&mutexFalling, NULL);
    pthread_t thread;

    while (1)
    {
        pthread_create(&thread, NULL, workerTask, NULL); // make a new thread for each falling number.
        usleep(55000);                                   // The function usleep() is a C API that suspends the current process for the number of microseconds passed to it. It can be used for delaying a job.
    }

    pthread_mutex_destroy(&mutexFalling);

    // usleep(10000000);
    endwin();
    return 0;
}