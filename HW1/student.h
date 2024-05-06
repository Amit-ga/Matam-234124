#ifndef STUDENT_H_
#define STUDENT_H_

#include "date.h"
#include "list.h"

/**
* STUDENT ADT
*
* Implements a student data type.
* each student has a name (type char*), a unique id (type int) ,
* and the number of events that the students is responsible of (type int)

* The following functions are available:
*   studentCreate		                - Creates a new empty student
*   studentDestroy		                - Deletes an existing student and frees all resources
*   studentCopy		                    - Copies an existing student
*   equalStudents  	                    - identifies equal students by their id
* 	getStudentName                      - Returns the name associated with a specific student
*	getStudentId                        - Returns the id associated with a specific student
*	getStudentEvents                    - Returns the number of events a given student is responsible for
*	setStudentName                      - Sets the name of a stuednt to a given name.
*	setStudentId                        - Sets the id of a stuednt to a given id.
*	setStudentEvents                    - Sets the events that a student is responsible for to a given number.
*/

typedef struct Student_t* Student;

/**
* studentCreate: Allocates a new empty student.
*
* @return
* 	NULL - if allocations failed.
* 	A new student in case of success.
*/
Student studentCreate();

/**
* studentDestroy: Deallocates an existing student. frees all elements.
*
* @param student - Target student to be deallocated. If student is NULL nothing will be done
*/
void studentDestroy(Student student);

/**
* studentCopy: Creates a copy of target student.
*
* @param student - Target student.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A new student the same as s otherwise.
*/
Student studentCopy(Student student);

/**
* equalStudents: identifies equal students by their id.
*
* @param student1 - first target student to be compared.
* @param student2 - second target student to be compared.
* @return
* 		false if the 2 students don't have the same id or one of them is NULL
* 		true if the 2 students have the same id
*/
bool equalStudents(Student student1, Student student2);

/**
*	getStudentName: Returns the name associated with a specific student
*
* @param student - The student for which to get the name.
*
* @return
*  NULL if a NULL pointer was sent.
*  The name associated with the student otherwise.
*/
char* getStudentName(Student student);

/**
*	getStudentId: Returns the id associated with a specific student
*
* @param student - The student for which to get the id.
*
* @return
*  NULL if a NULL pointer was sent.
*  The id associated with the student otherwise.
*/
int getStudentId(Student student);

/**
*	getStudentEvents: Returns the number of events a given student is responsible for
*
* @param student - The student for which to get the number of events
*
* @return
*  NULL if a NULL pointer was sent.
*  The number of events the student is responsible for otherwise.
*/
int getStudentEvents(Student student);

/**
*	setStudentName: Sets the name of a stuednt to a given name.
*
* @param student - The student for which to assign the new name
* @param name - The name which needs to be assigned.
*
*/
void setStudentName(Student student, char* name);

/**
*	setStudentId: Sets the id of a stuednt to a given id.
*
* @param student - The student for which to assign the new id
* @param id - The id which needs to be assigned.
*
*/
void setStudentId(Student student, int id);

/**
*	setStudentEvents: Sets the events that a student is responsible for to a given number.
*
* @param student - The student for which to assign the new number of events
* @param events - The number of events which needs to be assigned.
*
*/
void setStudentEvents(Student student, int events);

#endif //STUDENT_H_