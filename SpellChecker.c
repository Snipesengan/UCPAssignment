/*
 * File       : SpellChecker.c
 * Author     : Nhan Dao
 * References : N/A
 * Purpose    : Spell checker program, what else?
 */

#include <stdio.h>
#include "spellconf.h"
#include "FileIO.h"
#include "ActionFunc.h"
#include "check.h"

void freeWordArray(char** wordArray,int numWord)
{
    int i;
    for(i = 0; i < numWord; i++)
    {
        free(wordArray[i]);
        wordArray[i] = NULL;
    }
    free(wordArray);
    wordArray = NULL;
}

int main (int argc, char* argv[])
{
    SpellConf* configStruct = NULL;
    char** dictionary = NULL,**user_file = NULL;
    ActionFunc func = NULL;
    int numWord = 0, numDictWord = 0;

    if(argc == 2)
    {
        printf("\n\n==========SPELL CHECKER==========\n");
        printf("Reading .spellconf...\n");
        configStruct = readSpellConfFile(NULL);
        printf("---------------------------------\n");
        printf("Reading user file...\n"); 
        user_file = textToArray(argv[1], &numWord);   
        printf("---------------------------------\n");

        if(configStruct != NULL)
        {
            printf("Reading dictionary file...\n");    
            dictionary = textToArray(configStruct->dictfile, &numDictWord);
            printf("---------------------------------\n");
        }

        if(configStruct == NULL || user_file == NULL || dictionary == NULL)
        {    
            if(user_file == NULL)
            {
                free(configStruct);
                freeWordArray(dictionary,numDictWord);
            }

            if(dictionary == NULL)
            {
                free(configStruct);
                freeWordArray(user_file,numWord);
            }
        }
        else
        {
            if(configStruct->autocorrect == TRUE)
            {
                func = &autoCorrect;
            }
            else
            {
                func = &selfCorrect;
            }
           
            check(user_file,numWord,dictionary,numDictWord,configStruct->maxdifference
                  ,func);

            writeWordsToFile(argv[1],user_file,numWord);
            free(configStruct);
            freeWordArray(user_file,numWord);
            freeWordArray(dictionary,numDictWord);
        }

        printf("---------------------------------\n");
        printf("Finished...\n");
    }
    else
    {
        printf("Error, invalid command line paramters\n");
    }

    return 0;
}
    
