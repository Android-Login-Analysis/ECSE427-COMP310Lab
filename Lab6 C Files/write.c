#include <stdio.h>

int main()
{
    // Open file for writing
    FILE *file = fopen("output.txt", "w");
    // Check if the file opens successfully
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    const char *text = "Hello, World!\n";
    fputs(text, file); // Write text to the file
    fclose(file);      // Close the file
    return 0;
}
