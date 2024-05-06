#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "auxiliaries.h"

#define UNINITIALIZED -1;

struct Student_t {

	char* name; //  member_name
	int id; //  member_id
	int events; // number of events the student is associated with

};

Student studentCreate()
{
	Student new_student = malloc(sizeof(*new_student));
	if (new_student == NULL)
	{
		return NULL;
	}
	new_student->name = NULL;
	new_student->id = UNINITIALIZED;
	new_student->events = 0;

	return new_student;
}
void studentDestroy(Student student)
{
	free(student->name);
	free(student);
}
Student studentCopy(Student student)
{
	if (student == NULL)
	{
		return NULL;
	}
	Student new_student = studentCreate();

	if (new_student == NULL)
	{
		return NULL;
	}

	char* new_name = copyString(student->name);
	if (new_name == NULL)
	{
		studentDestroy(new_student);
		return NULL;
	}
	new_student->name = new_name;
	new_student->id = student->id;
	new_student->events = student->events;

	return new_student;
}
bool equalStudents(Student student1,Student student2)
{
	if (student1 == NULL || student2 == NULL)
	{
		return false;
	}

	if (student1->id== student2->id)
	{
		return true;
	}

	return false;
}

char* getStudentName(Student student)
{
	if (student == NULL)
	{
		return NULL;
	}

	return student->name;

}

int getStudentId(Student student)
{
	if (student == NULL)
	{
		return -1;
	}

	return student->id;
}

int getStudentEvents(Student student)
{
	if (student == NULL)
	{
		return -1;
	}

	return student->events;
}

void setStudentName(Student student, char* name)
{
	if (student != NULL)
	{
		student->name = name;
	}
}

void setStudentId(Student student, int id)
{
	if (student != NULL)
	{
		student->id = id;
	}
}

void setStudentEvents(Student student, int events)
{
	if (student != NULL)
	{
		student->events = events;
	}
}