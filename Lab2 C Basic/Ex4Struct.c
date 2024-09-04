// Exercise: Define a structure Student that contains
// a student's name and grade. In the main function,
// create a Student variable, initialize it with values,
// and then print the student's information.
#include <stdio.h>

struct Student
{
    char name[50];
    int grade;
};

int main()
{
    struct Student student1 = {"John Smith", 88};
    printf("Student Name: %s, Grade: %d\n", student1.name, student1.grade);
    return 0;
}
