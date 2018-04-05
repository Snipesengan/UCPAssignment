#include <stdio.h>
#include "LinkedList.h"

int main(void)
{
    int numTest;
    int numPass;
    char* testString[5];
    LinkedList* ll;

    printf("TESTING LinkedList.c\n");
    printf("Run with valgrind to check for memory leaks\n");
    printf("-------------------------------------------\n");

    numTest = 1;
    printf("TEST 1 - creating of list using newLinkedList()\n");
    ll = newLinkedList();
    numPass = 1;

    numTest++;
    printf("TEST 2 - asserting the list is empty: ");
    
    if(ll->numNode == 0)
    {
        printf("passed\n"); 
        numPass++;
    }
    else
    {
        printf("failed\n");
    }
    
    numTest++;   
    printf("TEST 3 - testing insert/remove first: ");
    
    testString[0] = "abc";
    testString[1] = "def";
    testString[2] = "ghi";
    testString[3] = "jkl";
    testString[4] = "lmn";
   
    insertFirst(ll, testString[0]);
    insertFirst(ll, testString[1]);
    insertFirst(ll, testString[2]);
    insertFirst(ll, testString[3]);
    insertFirst(ll, testString[4]);

    if((ll->numNode == 5)                           &&
       (strcmp((char*) removeFirst(ll),"lmn") == 0) &&
       (strcmp((char*) removeFirst(ll),"jkl") == 0) &&
       (strcmp((char*) removeFirst(ll),"ghi") == 0) &&
       (strcmp((char*) removeFirst(ll),"def") == 0) &&
       (strcmp((char*) removeFirst(ll),"abc") == 0) &&
       (ll->numNode == 0))
    {
        printf("passed\n");
        numPass++;
    }
    else
    {
        printf("failed\n");
    }

    numTest++;
    printf("TEST 4 - testing insert/remove last: "); 

    insertLast(ll, testString[0]);
    insertLast(ll, testString[1]);
    insertLast(ll, testString[2]);
    insertLast(ll, testString[3]);
    insertLast(ll, testString[4]);

    if((ll->numNode == 5)                          &&
       (strcmp((char*) removeLast(ll),"lmn") == 0) &&
       (strcmp((char*) removeLast(ll),"jkl") == 0) &&
       (strcmp((char*) removeLast(ll),"ghi") == 0) &&
       (strcmp((char*) removeLast(ll),"def") == 0) &&
       (strcmp((char*) removeLast(ll),"abc") == 0) &&
       (ll->numNode == 0))
    {
        printf("passed\n");
        numTest++;
    }
    else
    {
        printf("failed\n");
    }

    numTest++;
    printf("TEST 6 - freeing the list: ");
    softFreeList(ll);
    printf("passed\n");
    numPass++;

    return 0;
}      
       
    
