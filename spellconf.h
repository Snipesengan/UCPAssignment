/*
 * File       : spellconf.h
 * Author     : Nhan Dao
 * References : N/A
 * Purpose    : the stuct to store settings for the spell checker program
 * Comments   : N/A
 */

#ifndef SPELL_CONF_H
#define SPELL_CONF_H

#define SPELL_CONF_DEFAULT_PATH ".spellconf"
#define MAX_FILE_NAME 256

/*String to look in the file for the setting*/
/*MUST BE LESS THAN 30 CHARACTER*/

#define DICT_FILE "dictfile"
#define MAX_DIFFERENCE "maxdifference"
#define AUTO_CORRECT "autocorrect"

typedef struct 
{
    char dictfile[MAX_FILE_NAME];/* 255 is the maximum number char in a file name */
    int maxdifference;
    int autocorrect;
}SpellConf;
#endif
