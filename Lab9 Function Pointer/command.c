#include <stdio.h> // Include standard input/output library for using printf function

// Define three functions that represent different operations or commands
void start()
{
    printf("Starting...\n"); // Prints "Starting..." when this function is called
}
void stop()
{
    printf("Stopping...\n"); // Prints "Stopping..." when this function is called
}
void restart()
{
    printf("Restarting...\n"); // Prints "Restarting..." when this function is called
}

// Declare an array of function pointers, initialized with the addresses of start, stop, and restart functions
void (*actions[])(void) = {start, stop, restart};

// Main function where the program execution begins
int main()
{
    int action = 2; // Index of the function to be called, assumed to be obtained from user input or program logic

    // Call the function based on the index in 'action'
    actions[action](); // The function pointer array is indexed and the corresponding function is called

    return 0; // Return statement indicating successful execution of the program
}
