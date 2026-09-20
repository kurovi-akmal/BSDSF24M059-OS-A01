#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/myfilefunctions.h"

int wordCount(FILE* file, int* lines, int* words, int* chars)
{
    if (!file || !lines || !words || !chars)
        return -1;

    *lines = *words = *chars = 0;
    int c, inWord = 0;

    while ((c = fgetc(file)) != EOF)
    {
        (*chars)++;

        if (c == '\n')
            (*lines)++;

        if (isspace(c))
            inWord = 0;
        else if (!inWord)
        {
            (*words)++;
            inWord = 1;
        }
    }

    return 0;
}

int mygrep(FILE* fp, const char* search_str, char*** matches)
{
    if (!fp || !search_str || !matches)
        return -1;

    char line[1024];
    int count = 0;

    *matches = malloc(100 * sizeof(char*));
    if (!*matches)
        return -1;

    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, search_str))
        {
            (*matches)[count] = malloc(strlen(line) + 1);

            if (!(*matches)[count])
                return -1;

            strcpy((*matches)[count], line);
            count++;
        }
    }

    return count;
}