/*
 * File       : ActionFunc.h
 * Author     : Nhan Dao
 * References : N/A
 * comments   : N/A
 */

#ifndef ACTION_FUNC_H
#define ACTION_FUNC_H

#ifndef MAX_WORD_CHAR
#define MAX_WORD_CHAR 30
#endif

#include <string.h>
#include <stdlib.h>

int autoCorrect(char*, char*);
int selfCorrect(char*, char*);
#endif
