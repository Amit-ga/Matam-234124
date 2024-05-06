#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include "auxiliaries.h"
#include "event.h"
#include "date.h"
#include "student.h"


#define FIRST_IS_BIGGER 2
#define SECOND_IS_BIGGER -2
#define EQUAL 0
#define ERROR 0

char* copyString(const char* str)
{
	char* newStr = malloc(strlen(str) + 1);
	if (newStr == NULL)
	{
		return NULL;
	}
	return strcpy(newStr, str);
}

/* int Functions */

void* copyInt(void* e)
{
	if (e == NULL)
	{
		return NULL;
	}
	int* newInt = malloc(sizeof(int));
	if (newInt == NULL)
	{
		return NULL;
	}
	*newInt = *(int*)e;
	return newInt;
}

void freeInt(void* e)
{
	free(e);
}

bool equalInt(void* e1, void* e2)
{
	if (e1 == NULL || e2==NULL)
	{
		return false;
	}

	return *(int*)e1 == *(int*)e2;
}

int compareInt(void* e1, void* e2)
{
	if (e1 == NULL || e2 == NULL)
	{
		return ERROR;
	}

	if (*(int*)e1 > * (int*)e2)
	{
		return FIRST_IS_BIGGER;
	}
	else
	{
		if (*(int*)e1 < * (int*)e2)
		{
			return SECOND_IS_BIGGER;
		}
	}

	assert(equalInt(e1, e2) == true);
	return EQUAL;

}

/* char* Functions */

void* copyStr(void* str)
{
	if (str == NULL)
	{
		return NULL;
	}
	return copyString(((char*)(str)));
}

void freeStr(void* str)
{
	free(str);
}

int compareString(void* str1, void* str2)
{
	if (str1 == NULL || str2==NULL)
	{
		return ERROR;
	}

	return strcmp(str1, str2);
}

bool equalStr(void* str1, void* str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		return false;
	}

	if (compareString(str1, str2) == EQUAL)
	{
		return true;
	}

	return false;
}

/* Event functions */

void* copyEventElement(void* element)
{
	return eventCopy(((Event)(element)));
}

void freeEventElement(void* element)
{
	eventDestroy(((Event)(element)));
}

 bool equalEventElements(void* element1, void* element2)
{
	return equalEvents(((Event)(element1)), ((Event)(element2)));
}


/* Date Functions */
void* copyDatePriority(void* priority)
{
	return dateCopy(((Date)(priority)));
}

void freeDatePriority(void* priority)
{
	dateDestroy(((Date)(priority)));
}
int compareDateElementPriorities(void* priority1, void* priority2)
{
	return dateCompare(((Date)(priority1)), ((Date)(priority2)));
}


/* Student functions */

void* copyStudentElement(void* element)
{
	return studentCopy(((Student)(element)));
}

void freeStudentElement(void* element)
{
	studentDestroy(((Student)(element)));
}

bool equalStudentElements(void* element1, void* element2)
{
	return equalStudents(((Student)(element1)), ((Student)(element2)));
}

