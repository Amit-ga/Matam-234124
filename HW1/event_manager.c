#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "event_manager.h"
#include "priority_queue.h"
#include "list.h"
#include "event.h"
#include "auxiliaries.h"
#include "date.h"
#include "student.h"

#define DOT '.'
#define COMMA ','
#define PARAMETERS_IN_DATE 3

struct EventManager_t {
	
	PriorityQueue event_queue; // queue of events
	Date current_date; //system date
	PriorityQueue cs_association_members; // queue of association members
	//element-student
	//priority:events number-int
};

/*static functions declarations*/

/**
* sortStudentsById: sorts students with the same events number by their id
*                   (lowest to highest)
*
*@param association_queue  - Target queue to be sorted
* @return
* 	a PriorityQueueResult
*/
static PriorityQueue sortStudentsById(PriorityQueue association_queue);

/**
* resultConvert: converts a PriorityQueueResult type to an EventManagerResult type
*
*@param result  - Target result to be converted
* @return
* 	an EventManagerResult 
*/
static EventManagerResult resultConvert(PriorityQueueResult result);

/**
* dateToString: converts a date type to a string
*
*@param d  - Target date to be converted
* @return
*   NULL if NULL was sent
* 	a new string (format: day.month.year) in case of success
*/
static char* dateToString(Date date);

/**
* intLen: calculates the number of digits in a number
*
*@param num  - Target number
* @return
* 	the number of digits in num
*/
static int intLen(int num);

/**
* intToString: converts an  int to a string
*
*@param num  - Target int to be converted
* @return
* 	a new string with the digints of num
*/
static char* intToString(int num);

/**
* memebersQueueToString: converts a priority queue of students to a string
*
*@param num  - Target queue to be converted
* @return
* 	a new string (format: name1,name2,...)
*/
static char* memebersQueueToString(PriorityQueue members);


/**
* reverseDateCompare: reverses the result of comparing a date
*
*@param result  - Target result to be converted
* @param  - 2 target elements to be compared.
* @return
* 		A positive integer if element1 is smaller than element2;
* 		0 if they're equal or one of the given elements is NULL;
*		A negative integer if element1 is bigger than element2
*/
static int reverseDateCompare(void* priority1, void* priority2);


/*end of static functions declarations*/

/*static functions implementation*/

static PriorityQueue sortStudentsById(PriorityQueue association_queue)
{
	if (association_queue == NULL)
	{
		return NULL;
	}

	PriorityQueue sorted = pqCopy(association_queue);

	if (sorted == NULL)
	{
		return NULL;
	}

	PriorityQueueResult result = PQ_SUCCESS;
	int size = pqGetSize(sorted);

	assert(size != -1);

	for (int i=0; i<size*size; i++)
	{
		Student prev = studentCopy(pqGetFirst(sorted));
		Student next = studentCopy(pqGetNext(sorted));

		while (next!=NULL)
		{

			if (getStudentEvents(prev) == getStudentEvents(next) && getStudentId(prev) > getStudentId(next))
			{
				int old_priority = getStudentEvents(prev);
				int new_priority = getStudentEvents(prev);
				//we want the element to be inserted last
				result = pqChangePriority(sorted, prev,&old_priority, &new_priority);

				assert(result != PQ_NULL_ARGUMENT && result != PQ_ELEMENT_DOES_NOT_EXISTS);
				studentDestroy(next);
				if (result == PQ_OUT_OF_MEMORY)
				{
					studentDestroy(prev);
					return NULL;
				}
				break;
			}

			else
			{
				studentDestroy(prev);
				prev = studentCopy(next);
				studentDestroy(next);
				next = studentCopy(pqGetNext(sorted));
			}
		}

		studentDestroy(prev);

	}

	return sorted;

}

static EventManagerResult resultConvert(PriorityQueueResult result)
{
	switch (result)
	{
			case PQ_SUCCESS:
				return EM_SUCCESS;
				break;

			  case  PQ_OUT_OF_MEMORY:
				  return EM_OUT_OF_MEMORY;
				  break;

			  case   PQ_NULL_ARGUMENT:
				  return EM_NULL_ARGUMENT;
				  break;

			  case   PQ_ERROR:
				  return EM_ERROR;
				  break;

				default:
					return EM_SUCCESS;
	}

	return EM_SUCCESS;
}
static int intLen(int num)
{
	if (num == 0)
	{
		return 1;
	}

	int cnt = 0;

	if (num < 0)
	{
		cnt++;
	}

	while (num != 0)
	{
		cnt++;
		num = num / 10;
	}
	return cnt;
}

static char* intToString(int num)
{
	int size = intLen(num);
	int numm_size = sizeof(char) * size;
    char* result = (char*)(malloc(numm_size + 1));
	if (result == NULL)
	{
		free(result);
		return NULL;
	}
	int return_val=sprintf(result, "%d", num);
	if (return_val < 0)
	{
		free(result);
		return NULL;
	}

	return result;
}

static char* dateToString(Date date)
{
	if (date == NULL)
	{
		return NULL;
	}

	int* day = malloc(sizeof(int));
	if (day == NULL)
	{
		return NULL;
	}

	int* month = malloc(sizeof(int));
	if (month == NULL)
	{
		free(day);
		return NULL;
	}

	int* year = malloc(sizeof(int));
	if (year == NULL)
	{
		free(day);
		free(month);
		return NULL;
	}

	bool flag=dateGet(date, day, month, year);
	if (flag == false)
	{
		free(day);
		free(month);
		free(year);
		return NULL;
	}

	int temp_arr[PARAMETERS_IN_DATE] = { *day,*month,*year };
	free(day);
	free(month);
	free(year);

	int lenght = 0;
	for (int i = 0; i < PARAMETERS_IN_DATE; i++)
	{
		lenght += intLen(temp_arr[i]);
	}
	//need to save space for dots and '\0'
	lenght += 3;

	char* result = malloc((lenght) * sizeof(char) + 3);
	if (result == NULL)
	{
		return NULL;
	}

	char* temp = result; //iterator for result string
	assert(temp != NULL);

	for (int i = 0; i < PARAMETERS_IN_DATE; i++)
	{
		char* date_parameters_str = intToString(temp_arr[i]);
		if (date_parameters_str == NULL)
		{
			return NULL;
		}
		
		char* temp2 = date_parameters_str; // iterator for day,year and month strings

		while (*temp2)
		{
			*temp = *temp2;
			temp++;
			temp2++;
		}
		free(date_parameters_str);

		if (i != PARAMETERS_IN_DATE - 1)
		{
			*temp = DOT;
			temp++;
		}


	}

	*temp = '\0';
	return result;
}

static char* memebersQueueToString(PriorityQueue members)
{
	if (members == NULL)
	{
		return NULL;
	}

	int lenght = 0;
	PQ_FOREACH(Student, iterator, members)
	{
		lenght += strlen(getStudentName(iterator));
	}

	//need to save place from the commas
	char* result = malloc((2 * lenght - 1) * sizeof(char));
	if (result == NULL)
	{
		return NULL;
	}

	char* temp = result; // iterator for result

	PQ_FOREACH(Student, iterator, members)
	{
		char* temp2 = getStudentName(iterator); // iterator for the names
		while (*temp2)
		{
			*temp = *temp2;
			temp2++;
			temp++;
		}
		*temp = COMMA;
		temp++;
	}

	temp--;
	*temp = '\0';

	return result;
}

static int reverseDateCompare(void* priority1, void* priority2)
{
	return -1 * compareDateElementPriorities(priority1, priority2);
}

/*end of static functions implementation*/

EventManager createEventManager(Date date)
{
	if (date == NULL)
	{
		return NULL;
	}

	EventManager em = malloc(sizeof(*em));
	if (em == NULL)
	{
		return NULL;
	}

	em->event_queue = pqCreate(copyEventElement, freeEventElement, equalEventElements, copyDatePriority, freeDatePriority, reverseDateCompare);

	if (em->event_queue == NULL)
	{
		destroyEventManager(em);
		return NULL;
	}

	Date new_date = dateCopy(date);
	if (new_date == NULL)
	{
		destroyEventManager(em);
		return NULL;
	}

	em->current_date = new_date;
	em->cs_association_members = pqCreate(copyStudentElement, freeStudentElement, equalStudentElements, copyInt, freeInt, compareInt);
	if (em->cs_association_members == NULL)
	{
		destroyEventManager(em);
		return NULL;
	}

	return em;

}

void destroyEventManager(EventManager em)
{
	if (em != NULL)
	{
		pqDestroy(em->event_queue);
		dateDestroy(em->current_date);
		pqDestroy(em->cs_association_members);
		free(em);
	}
}

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id)
{
	//element = name of event
	//priority = date of event
	
	//cant have the same names with the same dates
	//can have the same names with different dates
	//an event cant happen before date

	if (!em || !event_name || !date)
	{
		return EM_NULL_ARGUMENT;
	}

	if (compareDateElementPriorities(date, em->current_date) < 0)
	{
		return EM_INVALID_DATE;
	}

	if (event_id < 0)
	{
		return EM_INVALID_EVENT_ID;
	}

	Event temp_event = eventCreate();
	if (temp_event == NULL)
	{
		return EM_OUT_OF_MEMORY;
	}

	setEventDate(temp_event,date);
	setEventId(temp_event,event_id);
	setEventName(temp_event,event_name);

	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		if (equalElementsDateAndName(iterator, temp_event))
		{
			//do not touch user pointers
			pqDestroy(getEventAssociation(temp_event));
			free(temp_event);
			return EM_EVENT_ALREADY_EXISTS;
		}
		if (getEventId(iterator) == getEventId(temp_event))
		{
			pqDestroy(getEventAssociation(temp_event));
			free(temp_event);
			return EM_EVENT_ID_ALREADY_EXISTS;
		}
	}

	assert(em->event_queue != NULL && temp_event != NULL && date != NULL);
	PriorityQueueResult result= pqInsert(em->event_queue, temp_event, date);
	pqDestroy(getEventAssociation(temp_event));
	free(temp_event);
	
	if (result != PQ_SUCCESS)
	{
		return resultConvert(result);
	}

	return EM_SUCCESS;
}

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id)
{
	if (!em || !event_name)
	{
		return EM_NULL_ARGUMENT;
	}

	if (days < 0)
	{
		return EM_INVALID_DATE;
	}
	if (event_id < 0)
	{
		return EM_INVALID_EVENT_ID;
	}
	int* day = malloc(sizeof(int));
	if (day == NULL)
	{
		return EM_OUT_OF_MEMORY;
	}

	int* month = malloc(sizeof(int));
	if (day == NULL)
	{
		free(day);
		return EM_OUT_OF_MEMORY;
	}

	int* year = malloc(sizeof(int));
	if (day == NULL)
	{
		free(day);
		free(month);
		return EM_OUT_OF_MEMORY;
	}

	assert(day && month && year);

	dateGet(em->current_date, day, month, year);

	//just in case
	if (!day || !month || !year)
	{
		free(day);
		free(month);
		free(year);
		return EM_OUT_OF_MEMORY;
	}

	Date event_date = dateCreate(*day, *month, *year);

	free(day);
	free(month);
	free(year);

	if (event_date == NULL)
	{
		return EM_OUT_OF_MEMORY;
	}

	for (int i = 0; i < days; i++)
	{
		dateTick(event_date);
	}

	EventManagerResult result=emAddEventByDate(em, event_name, event_date, event_id);

	dateDestroy(event_date);

	return result;

}

EventManagerResult emRemoveEvent(EventManager em, int event_id)
{
	if (!em)
	{
		return EM_NULL_ARGUMENT;
	}

	if (event_id < 0)
	{
		return EM_INVALID_EVENT_ID;
	}
	
	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		assert(em->event_queue != NULL && iterator != NULL);
		if (getEventId(iterator) == event_id)
		{
			//decrease student event by one
			PQ_FOREACH(Student, iterator_s, getEventAssociation(iterator))
			{
				PQ_FOREACH(Student, iterator_s2, em->cs_association_members)
				{
					if (equalStudents(iterator_s, iterator_s2))
					{
						setStudentEvents(iterator_s2, getStudentEvents(iterator_s2) - 1);
						int old_priority = getStudentEvents(iterator_s2) + 1;
						int new_priority = getStudentEvents(iterator_s2);
						pqChangePriority(em->cs_association_members, iterator_s2, &old_priority, &new_priority);
						break;
					}

				}
			}
			pqRemoveElement(em->event_queue, iterator);

			return EM_SUCCESS;
		}
	}

	return EM_EVENT_NOT_EXISTS;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date)
{
	if (!em || !new_date)
	{
		return EM_NULL_ARGUMENT;
	}

	if (dateCompare(em->current_date, new_date) > 0)
	{
		return EM_INVALID_DATE;
	}
	if (event_id < 0)
	{
		return EM_INVALID_EVENT_ID;
	}

	Date local_date = dateCopy(new_date);
	if (local_date == NULL)
	{
		return EM_OUT_OF_MEMORY;
	}

	PriorityQueueResult result = PQ_ELEMENT_DOES_NOT_EXISTS;
	Event temp_event = NULL;

	//check if the event already exists in that name and in that date
	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		if (getEventId(iterator) == event_id)
		{
			result = PQ_SUCCESS;

			temp_event = eventCreate();
			if (temp_event == NULL)
			{
				dateDestroy(local_date);
				return EM_OUT_OF_MEMORY;
			}

			Date temp_date = dateCopy(new_date);
			if (temp_date == NULL)
			{
				dateDestroy(local_date);
				eventDestroy(temp_event);
				return EM_OUT_OF_MEMORY;
			}
			char* temp_name = copyString(getEventName(iterator));
			if (temp_name == NULL)
			{
				dateDestroy(local_date);
				dateDestroy(temp_date);
				eventDestroy(temp_event);
				return EM_OUT_OF_MEMORY;
			}
			setEventDate(temp_event, temp_date);
			setEventName(temp_event, temp_name);
			setEventId(temp_event, event_id);
		}
	}

	if (result == PQ_ELEMENT_DOES_NOT_EXISTS)
	{
		dateDestroy(local_date);
		return EM_EVENT_ID_NOT_EXISTS;
	}

	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		if (equalElementsDateAndName(iterator, temp_event) == true)
		{
			dateDestroy(local_date);
			eventDestroy(temp_event);
			return EM_EVENT_ALREADY_EXISTS;
		}
	}

	eventDestroy(temp_event);

	//change the piority's date
	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		if (getEventId(iterator) == event_id)
		{
			assert(em->event_queue != NULL && iterator != NULL && getEventDate(iterator) != NULL && new_date != NULL);
			result= pqChangePriority(em->event_queue, iterator, getEventDate(iterator), new_date);
			assert(result != PQ_ELEMENT_DOES_NOT_EXISTS && result!=PQ_NULL_ARGUMENT);
			if (result == PQ_OUT_OF_MEMORY)
			{
				dateDestroy(local_date);
				return EM_OUT_OF_MEMORY;
			}
			break;
		}
	}

	//change the element's date
	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		if (getEventId(iterator) == event_id)
		{
			dateDestroy(getEventDate(iterator));
			setEventDate(iterator,local_date);
		}
	}	

	return EM_SUCCESS;
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id)
{
	if (!em || !member_name)
	{
		return EM_NULL_ARGUMENT;
	}

	if (member_id < 0)
	{
		return EM_INVALID_MEMBER_ID;
	}

	assert(em->cs_association_members != NULL);

	PQ_FOREACH(Student, iterator, em->cs_association_members)
	{
		if (getStudentId(iterator) == member_id)
		{
			return EM_MEMBER_ID_ALREADY_EXISTS;
		}
	}
	
	Student temp_s = studentCreate();
	if (temp_s == NULL)
	{
		return EM_OUT_OF_MEMORY;
	}
	setStudentEvents(temp_s,0);
	setStudentId(temp_s,member_id);
	setStudentName(temp_s,member_name);

	Student new_s = studentCopy(temp_s);
	free(temp_s);
	if (new_s == NULL)
	{
		return EM_OUT_OF_MEMORY;
	}
	
	int* priority = malloc(sizeof(int));
	if (priority == NULL)
	{
		studentDestroy(new_s);
		return EM_OUT_OF_MEMORY;
	}
	*priority = getStudentEvents(new_s);
	PriorityQueueResult result= pqInsert(em->cs_association_members, new_s, priority);
	free(priority);

	studentDestroy(new_s);

	return resultConvert(result);

}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id)
{
	if (em == NULL)
	{
		return EM_NULL_ARGUMENT;
	}

	if (event_id < 0)
	{
		return EM_INVALID_EVENT_ID;
	}

	if (member_id < 0)
	{
		return EM_INVALID_MEMBER_ID;
	}

	assert(em->event_queue != NULL);

	PQ_FOREACH(Event, iterator_events, em->event_queue)
	{
		if (event_id == getEventId(iterator_events))
		{
			PQ_FOREACH(Student, iterator_students, em->cs_association_members)
			{
				if (member_id == getStudentId(iterator_students))
				{
					//check if event and student are already linked
					if (pqContains(getEventAssociation(iterator_events), iterator_students) == true)
					{
						return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
					}

					Student s = studentCopy(iterator_students);
					if (s == NULL)
					{
						return EM_OUT_OF_MEMORY;
					}
					setStudentEvents(s,getStudentEvents(s)+1);

					int* id = malloc(sizeof(int));
					if (id == NULL)
					{
						studentDestroy(s);
						return EM_OUT_OF_MEMORY;
					}
					
					*id = -1 * member_id;
					PriorityQueueResult result=pqInsert(getEventAssociation(iterator_events), s, id);
					free(id);
					studentDestroy(s);

					if (result != PQ_SUCCESS)
					{
						return resultConvert(result);

					}

					//add one to student events
					int old_priority = getStudentEvents(iterator_students);
					int new_priority = old_priority + 1;
					setStudentEvents(iterator_students, getStudentEvents(iterator_students) + 1);
					result=pqChangePriority(em->cs_association_members, iterator_students, &old_priority , &new_priority );
					assert(result != PQ_ELEMENT_DOES_NOT_EXISTS);

					return resultConvert(result);


				}

			}

			return EM_MEMBER_ID_NOT_EXISTS;
		}
	}

	return EM_EVENT_ID_NOT_EXISTS;
}

EventManagerResult emRemoveMemberFromEvent(EventManager em, int member_id, int event_id)
{
	if (em == NULL)
	{
		return EM_NULL_ARGUMENT;
	}

	if (event_id < 0)
	{
		return EM_INVALID_EVENT_ID;
	}

	if (member_id < 0)
	{
		return EM_INVALID_MEMBER_ID;
	}
	
	//keep the errors returning in the right order
	bool event_exists_in_em = false;
	PQ_FOREACH(Event, iterator, em->event_queue)
	{
		if (getEventId(iterator)==event_id)
		{
			event_exists_in_em = true;
		}
	}

	if (event_exists_in_em == false)
	{
		return EM_EVENT_ID_NOT_EXISTS;
	}


	bool student_exists_in_em = false;
	PQ_FOREACH(Student, iterator_students, em->cs_association_members)
	{
		if (member_id == getStudentId(iterator_students))
		{
			student_exists_in_em = true;
		}
	}

	if (student_exists_in_em == false)
	{
		return EM_MEMBER_ID_NOT_EXISTS;
	}


	assert(em->event_queue != NULL);

	PQ_FOREACH(Event, iterator_events, em->event_queue)
	{
		//event exists
		if (event_id == getEventId(iterator_events))
		{
			PQ_FOREACH(Student, iterator_students, getEventAssociation(iterator_events))
			{
				//student is linked to event
				if (member_id == getStudentId(iterator_students))
				{
					PriorityQueueResult result= pqRemoveElement(getEventAssociation(iterator_events), iterator_students);
					if (result == PQ_SUCCESS)
					{
						PQ_FOREACH(Student, main_iterator_students, em->cs_association_members)
						{
							if (member_id == getStudentId(main_iterator_students))
							{
								assert(em->cs_association_members != NULL && main_iterator_students != NULL);
								int old_priority = getStudentEvents(main_iterator_students);
								int new_priority = getStudentEvents(main_iterator_students) - 1;
								setStudentEvents(main_iterator_students , getStudentEvents(main_iterator_students)-1);
								result= pqChangePriority(em->cs_association_members, main_iterator_students, &old_priority, &new_priority);

								return resultConvert(result);
							}
						}

						return EM_EVENT_AND_MEMBER_NOT_LINKED; // should not get here
					}

					assert(result != PQ_ELEMENT_DOES_NOT_EXISTS);
					return resultConvert(result);	
				}
			}

			return EM_EVENT_AND_MEMBER_NOT_LINKED;
		}
	}

	return EM_EVENT_ID_NOT_EXISTS;
}

EventManagerResult emTick(EventManager em, int days)
{
	if (em == NULL)
	{
		return EM_NULL_ARGUMENT;
	}

	if (days <= 0)
	{
		return EM_INVALID_DATE;
	}

	assert(em->current_date != NULL);

	for (int i = 0; i < days; i++)
	{
		dateTick(em->current_date);
	}

	int size = pqGetSize(em->event_queue);

	PriorityQueueResult result = PQ_SUCCESS;

	for (int i = 0; i < size; i++)
	{
		PQ_FOREACH(Event, iterator, em->event_queue)
		{
			if (compareDateElementPriorities(em->current_date, getEventDate(iterator)) > 0)
			{
				PQ_FOREACH(Student, iterator_s, getEventAssociation(iterator))
				{
					PQ_FOREACH(Student, iterator_s2, em->cs_association_members)
					{
						if (equalStudents(iterator_s, iterator_s2) == true)
						{
							setStudentEvents(iterator_s2, getStudentEvents(iterator_s2) - 1);
							int old_priority = getStudentEvents(iterator_s2) + 1;
							int new_priority = getStudentEvents(iterator_s2);
							result  = pqChangePriority(em->cs_association_members, iterator_s2, &old_priority, &new_priority);
							if (result != PQ_SUCCESS)
							{
								return resultConvert(result);
							}
						}

					}
				}


				result= pqRemoveElement(em->event_queue, iterator);
				if (result != PQ_SUCCESS)
				{
					return resultConvert(result);
				}
			}
		}

	}

	return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em)
{
	if (em == NULL)
	{
		return -1;
	}

	return pqGetSize(em->event_queue);
}

char* emGetNextEvent(EventManager em)
{
	if (em == NULL || em->event_queue==NULL)
	{
		return NULL;
	}

	Event e=pqGetFirst(em->event_queue);

	if (e == NULL)
	{
		return NULL;
	}

	return getEventName(e);
}

void emPrintAllEvents(EventManager em, const char* file_name)
{
	if (em == NULL || file_name == NULL)
	{
		return;
	}

	//opening the file for reading
	FILE* file = fopen(file_name, "w");
	if (file == NULL)
	{
		return;
	}

	PQ_FOREACH(Event, iterator, em->event_queue)
	{

		assert(getEventDate(iterator) != NULL);
		assert(getEventAssociation(iterator) != NULL);

		char* event_date = dateToString(getEventDate(iterator));

		if (event_date == NULL)
		{
			return;
		}

		char* event_memebers = NULL;
		if (pqGetFirst(getEventAssociation(iterator)) != NULL)
		{
			event_memebers = memebersQueueToString(getEventAssociation(iterator));
			if (event_memebers == NULL)
			{
				free(event_date);
				return;
			}
		}

		fputs(getEventName(iterator), file);
		fputs(",", file);
		fputs(event_date, file);
		if (event_memebers != NULL)
		{
			fputs(",", file);
			fputs(event_memebers, file);
		}
		free(event_date);
		free(event_memebers);

		fputs("\n", file);
	}

	fclose(file);
}
void emPrintAllResponsibleMembers(EventManager em, const char* file_name)
{
	if (em == NULL || file_name == NULL)
	{
		return;
	}

	FILE* file = fopen(file_name, "w");
	if (file == NULL)
	{
		return;
	}

	PriorityQueue sorted = sortStudentsById(em->cs_association_members);

	if (sorted == NULL)
	{
		return;
	}
	

	PQ_FOREACH(Student, iterator, sorted)
	{
		if (getStudentEvents(iterator) == 0)
		{
			continue;
		}


		char* events_num_str = intToString(getStudentEvents(iterator));
		if (events_num_str == NULL)
		{
			return;
		}
		//need to dave place for the comma
		fputs(getStudentName(iterator), file);
		fputs(",", file);
		fputs(events_num_str, file);
		free(events_num_str);

		fputs("\n", file);

	}

	fclose(file);
	pqDestroy(sorted);
}