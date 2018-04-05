/*
 * File       : FileIO.c
 * Author     : Nhan dao
 * References : N/A
 * Purpose    : This .c file handles input/output for spell-checker program
 * Comments   :
 *
 * This programs handles the input/output from files for the spell-checker program.
 * INPUT:
 *     - A text file to check
 *     - A dictionary file
 *     - A settings file
 *
 *
 * NOTE:
 *     For reason relating to performance, we will try to read the file only once
 */

#include "FileIO.h"
#define INPUT_SIZE ((MAX_FILE_NAME) + 31)


static char** makeWordArray(LinkedList*, int*);
static void freeWord(void*);
static int tokenize(char*, size_t*, SpellConf*);
static int specialChar(char);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose: This method takes in an array of strings and words and output them     *
 *          to a file.                                                             *
 * Import: fileName (char*), array of words (char**), number of words (int)        *
 * Export: Output to file                                                          *
 * Assertion: None                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int writeWordsToFile(char* path, char** wordArray, int numWord)
{
    FILE* f;
    int error = FALSE, index;
    
    f = fopen(path, "w");
    
    if(f == NULL)/*If the file does not exists*/
    {
        perror("Could not open the file");
    }
    else/*If the file exists*/
    {
        index = 0;
        while(!error && index < numWord)/*Iterate through the word array*/
        {
            fprintf(f,"%s ", wordArray[index]);/*prints to the file with a space*/
            index++;
            error = ferror(f);
        }
    }

    if(error)
    {
        perror("An error has occured while writing to the file");
    }
    
    if(fclose(f))
    {
        perror("Could not close the file");
    }

    return error;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose: This method reads the configuration file and output the appropriate    *
 *          struct                                                                 *
 * Import: file name (char*)                                                       *
 * Export: struct pointer (SpellConf*)                                             *
 * Assertion: file must be valid                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

SpellConf* readSpellConfFile(char* path)
{
    FILE* f;
    SpellConf* sp;
    size_t nRead;
    char str[INPUT_SIZE];
    int error;

    if(path != NULL)
    {   
        f = fopen(path, "r");
    }
    else
    {
        f = fopen(SPELL_CONF_DEFAULT_PATH,"r");
    }

    if(f == NULL)
    {
        sp = NULL;
        perror("Could not open the file\n");
    }
    else
    {
        /*nRead represents the state of the number of read parameters*/
        /*Since there is three parameter to be read, dictfile, maxdifference, autocorrect, 3 bits*/
        /*are needed to represent the state*/
        nRead = 0b000;
        sp = (SpellConf*) malloc(sizeof(SpellConf));
        error = 0;        

        while(fgets(str, INPUT_SIZE, f) != NULL && error == 0)
        {
            /*tokenize will parse the neccessary value from the string
            import it into the struct 'sp'*/
            error += tokenize(str,&nRead,sp); 
            error += ferror(f);
        }

        if(error > 0)
        {
            free(sp);
            sp = NULL;
            printf("An error occured while reading the file\n");
        }
        else
        {
            printf("Successfully read the file\n");
        }

        if(fclose(f) != 0)
        {
            perror("There was an error closing the file");
        }
    }

    return sp;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose: Takes a file and returns the number of words and an array of string    * 
 * Import: file name (char*)                                                       *
 * Export: array of string (char**), number of words (int*)                        *
 * Assertion: file must be valid                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char** textToArray(char* path, int* numWord)
{
    FILE* f;
    LinkedList* ll; /*The linked list is used to cache the data*/
    int numChar,error,eof;
    char word_buffer[MAX_WORD_CHAR + 1], chr, *word;
    char** wordArray;

    f = fopen(path, "r");

    if(f == NULL)
    {
        perror("Could not open the file");
        wordArray = NULL;
    }
    else /*file is readable */
    {
        ll = newLinkedList();
        numChar = 0;
        error = FALSE;
        eof = FALSE;
        
        while(!eof && !error)
        {
            if(feof(f)) /*if end of file is reached*/
            {
                eof = TRUE;
                if(numChar > 0)/*if there is still characters left in the word buffer*/
                {
                    word = (char*) malloc((numChar + 1) * sizeof(char));
                    strncpy(word,word_buffer,numChar);
                    word[numChar] = '\0';
                    insertLast(ll,word);
                }
            }
            else
            {
                chr = fgetc(f);
                error = ferror(f);

                if(numChar == MAX_WORD_CHAR)/*If the number of char buffered reached the maximum*/
                {
                    error = TRUE;
                }
                else if(numChar > 0  && specialChar(chr))/*If a special character is encountered. i.e ' ','\n','\0'*/
                {
                    /*the following copy the characters in word_buffer into a malloc char array*/
                    /*the word then get insert into the linked-list*/
                    word = (char*) malloc((numChar + 1) * sizeof(char));
                    strncpy(word,word_buffer,numChar);
                    word[numChar] = '\0';
                    insertLast(ll,word);      
                    numChar = 0;/*reset the number word counter*/
                }
                else
                {
                    if(!specialChar(chr))/*put the character onto the word buffer if its not a special character*/
                    {
                        word_buffer[numChar] = chr;
                        numChar++;
                    }
                }
            }

        }

        if(error)
        {
            wordArray = NULL;
            hardFreeList(ll,&freeWord);/*free the link list and all the data it contains, freeWord is the function to free the data*/
            printf("An error has occured while reading the file\n");
        }
        else/*if theres no error*/
        {
            wordArray = makeWordArray(ll, numWord);/*Create the word array using the linked list*/
            softFreeList(ll);/*free the link list but not the data*/
            printf("Successfully read the file\n");
        }

        if(fclose(f) != 0)
        {
            perror("Could not close the file");
        }
    }

    return wordArray;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:  Takes a line from .spellconf and tokenize it and store it in a        *
 *           SpellConf struct                                                      * 
 * Import: string (char*)                                                          *
 * Export: number of read items so far (size_t), error (int), sp (SpellConf*)      *
 * Assertion: the setting parameter must not have already been read in             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static int tokenize(char* str, size_t* nRead, SpellConf* sp)
{
    int error;
    char tok1[INPUT_SIZE];           
    char tok2[INPUT_SIZE];
    int val;

    /* Regarding the code above ^:
     * The string will be split into two tokens, tok1 & tok2. It may seem redudant making the
     * the size of each token to INPUT_SIZE which is the maximum size of the string. Since,
     * tok1 + tok2 <= INPUT_SIZE. But this ensure that we are protected from buffer overflow
     * attack if someone decides to purposefully tokenize the string to make tok1 be the whole
     * string itself.
     */

    error = TRUE;
    if(sscanf(str,"%s = %s",tok1,tok2) == 2)/*assert that two token has been parsed*/
    {
        if(strncmp(DICT_FILE,tok1,INPUT_SIZE) == 0)/*If the parameter relate to dictfile*/
        {
            if((*nRead & 0b100) == 0b000)/*check if this parameter has not been read*/
            {
                strncpy(sp->dictfile,tok2,MAX_FILE_NAME);
                *nRead = *nRead | 0b100; /*update the paramter to been read*/
                error = FALSE;
            }   
        }
        else if(strncmp(MAX_DIFFERENCE,tok1,INPUT_SIZE) == 0)/*If parameter realate to maxdifference*/
        {
            if((*nRead & 0b010) == 0b000)/*check if this parameter has not been read*/
            {
                val = atoi(tok2);
                if(val > 0)
                {
                    sp->maxdifference = val;
                    error = FALSE;
                }

                *nRead = *nRead | 0b010;/*update the paramter to been read*/
            }                 
        }
        else if(strncmp(AUTO_CORRECT,tok1,INPUT_SIZE) == 0)/*If parameter relate to autocorrect*/
        {
            if((*nRead & 0b001) == 0b000)/*check if this parameter has not been read*/
            {
                if(strncmp("yes",tok2,4) == 0)
                {
                    sp->autocorrect = TRUE;
                    error = FALSE;
                }
                else if(strncmp("no",tok2,3) == 0)
                {
                    sp->autocorrect = FALSE;
                    error = FALSE;
                }

                *nRead = *nRead | 0b001;/*update the paramter to been read*/
            }
        }
    }

    return error;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Purpose:  Create an array of words (char*) from a linked list                   *
 *           SpellConf struct                                                      * 
 * Import: LinkedList*                                                             *
 * Export: Array of words (char**), number of words (int*)                         *
 * Assertion: There are more than 0 words in the linked list                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static char** makeWordArray(LinkedList* ll, int* numWord)
{
    char** wordArray;
    int index;

    *numWord = ll->numNode;
    if(*numWord > 0)   
    {
        wordArray = (char**) malloc(*numWord * sizeof(char*));/*malloc the word array*/
        index = 0;

        while(ll->head != NULL)
        {
            wordArray[index] = (char*) removeFirst(ll);
            index++;
        }
    }
    else
    {
        wordArray = NULL;
    }

    return wordArray;
}

/*This function is used to free the word used by LinkedList*/
static void freeWord(void* data)
{
    char* chr = (char*) data;
    free(chr);
}


/*Characters that are not considered to be part of a word*/
static int specialChar(char chr)
{
    int isSpecial = TRUE;
    
    if((chr >= 'A' && chr <= 'Z') || 
       (chr >= 'a' && chr <= 'z') ||
       (chr == '-')             )
    {
        isSpecial = FALSE;
    }
 
    return isSpecial;
}
