#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int age;
} Person;

Person *create_person(const char *name, int age)
{
    Person *person = (Person *)malloc(sizeof(Person));
    if (!person)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    person->name = (char *)malloc(strlen(name) + 1);
    if (!person->name)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(person); // Free person if name allocation fails
        exit(1);
    }
    strcpy(person->name, name);
    person->age = age;
    return person;
}

void delete_person(Person *person)
{
    free(person->name);
    free(person); // Normal memory deallocation
}

void process_people()
{
    Person *p1 = create_person("Alice", 30);
    Person *p2 = create_person("Bob", 25);

    printf("Processing: %s, %d\n", p1->name, p1->age);
    printf("Processing: %s, %d\n", p2->name, p2->age);

    // Error: mistakenly freeing p1's name again
    free(p1->name);
    delete_person(p1);

    delete_person(p2);
}

int main()
{
    process_people();
    return 0;
}
