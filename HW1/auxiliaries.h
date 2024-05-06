#ifndef AUXILARIES_H_
#define AUXILARIES_H_

#include <stdbool.h>

/**
* copyString - Copies an existing string
* Implements functions for generic ADTS to use.
* The following functions are available:
** Copy: Creates a copy of target element.
* @param  - Target element .
* @return
* 	     NULL if a NULL was sent or a memory allocation failed.
* 	     A new element, the same as target element otherwise.
** free: Deallocates an existing element.Frees all resources.
* @param  - Target element to be deallocated. 
  If elemnt is NULL nothing will be done
** Compare: compares 2 elements and return which comes first.
* @param  - 2 target elements to be compared.
* @return
* 		A negative integer if element1 is smaller than element2;
* 		0 if they're equal or one of the given elements is NULL;
*		A positive integer if element1 is bigger than element2
** equal: identifies equal elements.
* @param  - 2 target elements to be compared.
* @return
* 		true if the 2 elements are equal;
*		false otherwise;
*/


/**
* copyString: Creates a copy of target string.
*
* @param str - Target string to copy.
* @return
* 	NULL if a NULL was sent, or a memory allocation failed.
* 	A string containing the same elements as node param otherwise.
*/
char* copyString(const char* str);


/*
* functions for generic ADTS to use for copying,freeing and comparing an integer.
*/
void* copyInt(void* e);
void freeInt(void* e);
bool equalInt(void* e1, void* e2);
int compareInt(void* e1, void* e2);

/*
* functions for generic ADTS to use for copying,freeing and comparing a string.
*/
void* copyStr(void* str);
void freeStr(void* str);
int compareString(void* str1, void* str2);
bool equalStr(void* str1, void* str2);

/*
* functions for generic ADTS to use for copying,freeing and comparing an event.
*/
void* copyEventElement(void* element);
void freeEventElement(void* element);
bool equalEventElements(void* element1, void* element2);

/*
* functions for generic ADTS to use for copying,freeing and comparing a date.
*/
void* copyDatePriority(void* priority);
void freeDatePriority(void* priority);
int compareDateElementPriorities(void* priority1, void* priority2);

/*
* functions for generic ADTS to use for copying,freeing and comparing a student.
*/
void* copyStudentElement(void* element);
void freeStudentElement(void* element);
bool equalStudentElements(void* element1, void* element2);

#endif //AUXILARIES_H_