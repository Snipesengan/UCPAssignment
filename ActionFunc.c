/*
 * File       : ActionFunc.c
 * Author     : Nhan Dao
 * References : N/A
 * Purpose    : Create multiple function that handles word correction
 * Comments   :
 */

#include <stdio.h>
#include "check.h"
#include "ActionFunc.h"


static void flush(void);

int autoCorrect(char* word, char* suggestion)
{
    int success = FALSE;

    if(suggestion != NULL)
    {
        success = TRUE;
    }
    else
    {
        success = FALSE;
    }

    return success;
}

int selfCorrect(char* word, char* suggestion)
{
    int success = FALSE;
    char sel[20];

    printf("---------------------------------\n");
    if(suggestion != NULL)
    {
        printf("Correct \"%s\" -> \"%s\"?\n",word,suggestion);
        printf("Do you want to correct?(y/n): ");
        scanf(" %s", sel);
        flush();

        while(strncmp("y",sel,1) != 0 && strncmp("n",sel,1) != 0 && strlen(sel) != 1)
        {
            printf("Please enter 'y' or 'n', case-sensitive: ");
            scanf(" %s", sel);
            flush();
        }

        if(strncmp("y",sel,1) == 0)
        {
            success = TRUE;
        }
    }
    else
    {
        printf("Could not find any word suggestion for \"%s\"\n",word);
    }

    return success;
}

static void flush()
{
    char c;
    while((c=getchar()) != '\n' && c!=EOF){}
}
