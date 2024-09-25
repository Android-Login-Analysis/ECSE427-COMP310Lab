#include <stdio.h>
#include <stdlib.h>

float average(int numClass, int *classScores);

int main(void)
{
    int numClass;

    printf("Input the number of classes:\n");
    scanf("%d", &numClass);

    int *classScores = malloc(sizeof(int) * numClass);

    int idx = 0;
    while (idx < numClass)
    {
        printf("Input a score (between 0 and 100):\n");
        scanf("%d", classScores + idx);
        if (classScores[idx] > 0 && classScores[idx] <= 100)
        {
            idx++;
        }
        else
        {
            printf("Invalid score is given: %d\n", classScores[idx]);
        }
    }

    idx = 0;
    printf("Scores\n");
    while (idx < numClass)
    {
        printf("  class %d: %d\n", idx, classScores[idx]);
        idx++;
    }

    float avg = average(numClass, classScores);
    printf("Average: %f\n", avg);

    free(classScores);

    return 0;
}

float average(int numClass, int *classScores)
{
    int sum = 0;
    int idx = 0;
    while (idx < numClass)
    {
        sum += classScores[idx];
        idx++;
    }

    return sum / (float) numClass;
}
