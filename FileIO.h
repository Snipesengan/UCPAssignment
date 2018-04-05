/*
 * File       : FileIO.h
 * Author     : Nhan dao
 * References : https://en.wikipedia.org/wiki/Longest_word_in_English 
 *              To obtain the longest characters in a word
 * Comments   :
 * 
 * This is a header file for FileIO.c. Containing the necessary functions
 */


#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "spellconf.h"

#ifndef FALSE
#define FALSE 0
#define TRUE !(FALSE)
#endif

#define MAX_WORD_CHAR 50

SpellConf* readSpellConfFile(char* path);
char** textToArray(char* path, int* numWord);
char** readDictFile(char* path, int* numWord);
int writeWordsToFile(char*,char**,int);

#endif 
