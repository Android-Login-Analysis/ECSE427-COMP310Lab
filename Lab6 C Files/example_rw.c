#include <stdio.h>

void copyFileContent(FILE *source, FILE *target)
{
    char buffer[256];
    // Read from the source file and write to the target file
    while (fgets(buffer, sizeof(buffer), source) != NULL)
    {
        fputs(buffer, target);
    }
}

int main()
{
    // Open the input file
    FILE *inputFile = fopen("input.txt", "r");
    // Check if the input file opens successfully
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return -1;
    }
    // Open the output file
    FILE *outputFile = fopen("output.txt", "w");
    // Check if the output file opens successfully
    if (outputFile == NULL)
    {
        fclose(inputFile); // Close the input file
        perror("Error opening output file");
        return -1;
    }

    // Copy the content from input to output
    copyFileContent(inputFile, outputFile);

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");
    return 0;
}
