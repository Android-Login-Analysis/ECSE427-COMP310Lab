#include <stdio.h> // Include standard input/output library for printf function

// Define a struct named 'Sensor' with an integer and a function pointer as members
typedef struct
{
    int value;           // Integer to hold the sensor's current value
    void (*update)(int); // Function pointer for update method, takes an int parameter
} Sensor;

// Function to update the sensor value, prints the new value
void updateSensor(int newValue)
{
    printf("Sensor updated to %d\n", newValue); // Print the updated value to the console
}

// Main function where the program execution starts
int main()
{
    // Initialize a Sensor struct with value 0 and update function 'updateSensor'
    Sensor sensor = {0, updateSensor};

    // Call the update function through the function pointer with new value 100
    sensor.update(100); // This will update the sensor's value and print "Sensor updated to 100"

    return 0; // Return statement for the main function
}
