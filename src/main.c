#include <stdio.h>
#include <stdlib.h>

#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main()
{
    printf("--- Testing String Functions ---\n");

    char dest[100] = "Hello";
    char copy[100];

    printf("mystrlen: %d\n", mystrlen(dest));

    mystrcpy(copy, dest);
    printf("mystrcpy: %s\n", copy);

    mystrncpy(copy, "Programming", 5);
    printf("mystrncpy: %s\n", copy);

    mystrcpy(dest, "Hello ");
    mystrcat(dest, "World");
    printf("mystrcat: %s\n", dest);

    printf("\n--- Testing File Functions ---\n");

    FILE* file = fopen("test.txt", "r");

    if (file == NULL)
    {
        printf("Could not open test.txt\n");
        return 1;
    }

    int lines, words, chars;

    if (wordCount(file, &lines, &words, &chars) == 0)
    {
        printf("Lines: %d\n", lines);
        printf("Words: %d\n", words);
        printf("Characters: %d\n", chars);
    }

    rewind(file);

    char** matches;
    int count = mygrep(file, "Hello", &matches);

    printf("Matches: %d\n", count);

    for (int i = 0; i < count; i++)
    {
        printf("%s", matches[i]);
        free(matches[i]);
    }

    free(matches);
    fclose(file);

    return 0;
}