#include <stdio.h>

int main()
{
    // Open file for reading
    FILE *file = fopen("example.txt", "r");
    // Check if the file is opened successfully
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    char line[100];
    // Read the file line by line until end of file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line); // Print each line
    }
    fclose(file); // Close the file
    return 0;
}
