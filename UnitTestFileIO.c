/*
 * File        : UnitTestFileIO.c
 * Author      : Nhan Dao
 * References  : N/A
 * Purpse      : To test FileIO.c
 * Comments    : N/A
 */

#include <stdio.h>
#include "FileIO.h"
#define FILE_IO_TEST_FILE_1 "FileIO_TestFile_1.txt"
#define FILE_IO_TEST_FILE_2 "FileIO_TestFile_2.txt"


int main(void)
{
    int numTest,numPass;
    char** wordArray;
    int numWord,i,misMatch;
    char* correct_word[] = {"Rasheed","and","Cameron's","sexuality","are",
				    "somewhat","questionable"};
    int num_correct_word = 7;
    SpellConf* sp;
    char* dictfile = "Why are my meatballs so spicy";
    int maxdifference = 3;
    int autocorrect = FALSE;
    
    printf("TESTING FileIO.c\n");
    printf("Run with valgrind to check for memory leaks\n");
    printf("-------------------------------------------\n");

    numTest = 1;
    printf("TEST 1 - calling textToArray(..): \n");
    wordArray = textToArray(FILE_IO_TEST_FILE_1,&numWord);
    if(wordArray != NULL)
    {
        printf("passed\n");
        numPass = 1;
    }
    else
    {
        printf("failed\n");
    }

    numTest++;
    printf("TEST 2 - Asserting the word array is correct: \n");
    if(numWord == num_correct_word)
    {
        i = 0;
        misMatch = 0;
        while(i < numWord)
        {
            if(strncmp(correct_word[i],wordArray[i],MAX_WORD_CHAR) != 0)
            {
                misMatch++;
            }
            free(wordArray[i]);
            i++;
        }
        free(wordArray);

        if(misMatch > 0)
        {
            printf("failed, %d mismatch words\n",misMatch);
        }
        else
        {
            printf("passed\n");
            numPass++;
        }
    }
    else
    {
        printf("failed, incorrect number of words '%d'\n",numWord);
    }

    numTest++;
    printf("TEST 3 - calling readSpellConfFile(...): \n");
    sp = readSpellConfFile(FILE_IO_TEST_FILE_2);
    if(sp == NULL)
    {
        printf("failed\n");
    }
    else
    {
        printf("passed\n");
        numPass++;
    }

    numTest++;
    printf("TEST 4 - asserting concent of SpellConf struct: \n");
    if(strncmp(sp->dictfile,dictfile,MAX_FILE_NAME) &&
       sp->maxdifference == maxdifference           &&
       sp->autocorrect == autocorrect)
    {
        printf("passed\n");
        numPass++;
    }
    else
    {
        printf("failed\n");
    }
    
    numTest++;
    printf("TEST 5 - free'ing the SpellConf struct: \n");
    free(sp);
    printf("passed\n");
    numPass++;

    

    
    return 0;
}

