#include <stdio.h>

int main()
{
    // Attempt to open a file in read-only mode
    FILE *file = fopen("example.txt", "r");
    // Check if the file was successfully opened
    if (file == NULL)
    {
        perror("Error opening file"); // Print error message if opening fails
        return -1;
    }
    // Additional file operations go here
    fclose(file); // Close the file
    return 0;
}
