#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "event.h"
#include "auxiliaries.h"
#include "date.h"
#include "priority_queue.h"


#define UNINITIALIZED -1;
#define EQUAL 0

struct Event_t {

	char* name; // event name
	Date date;// event date
	int id; // unique id
	PriorityQueue event_association_members; // the association running the event
	//element-student
	//priority:id-int
};

Event eventCreate()
{
	Event new_event = malloc(sizeof(*new_event));
	if (new_event == NULL)
	{
		return NULL;
	}
	new_event->date = NULL;
	new_event->event_association_members = pqCreate(copyStudentElement, freeStudentElement, equalStudentElements, copyInt, freeInt, compareInt);
	new_event->id = UNINITIALIZED;
	new_event->name = NULL;

	return new_event;
}

void eventDestroy(Event my_event)
{

	free(my_event->name);
	dateDestroy(my_event->date);
	pqDestroy(my_event->event_association_members);
	free(my_event);

}

Event eventCopy(Event my_event)
{
	Event new_event = eventCreate();

	if (new_event == NULL)
	{
		return NULL;
	}

	char* new_str;

	if (my_event->name == NULL)
	{
		new_str = NULL;
	}
	else
	{
		new_str = copyString(my_event->name);
		if (new_str == NULL)
		{
			eventDestroy(new_event);
			return NULL;
		}
	}

	Date new_date = dateCopy(my_event->date);

	if (new_date == NULL)
	{
		eventDestroy(new_event);
		free(new_str);
		return NULL;
	}

	pqDestroy(new_event->event_association_members);

	PriorityQueue new_event_association_members = NULL;

	if (my_event->event_association_members == NULL)
	{
		new_event_association_members = NULL;
	}

	else
	{
		new_event_association_members = pqCopy(my_event->event_association_members);
		if (new_event_association_members == NULL)
		{
			eventDestroy(new_event);
			free(new_str);
			dateDestroy(new_date);
			return NULL;
		}
	}

	new_event->name = new_str;
	new_event->date = new_date;
	new_event->event_association_members = new_event_association_members;
	new_event->id = my_event->id;

	return new_event;

}

bool equalEvents(Event my_event1, Event my_event2)
{
	if (my_event1 == NULL || my_event2 == NULL)
	{
		return false;
	}
	if (my_event1->id == my_event2->id)
	{
		return true;
	}

	return false;
}

bool equalElementsDateAndName(Event my_event1, Event my_event2)
{
	if (my_event1 == NULL || my_event2 == NULL)
	{
		return false;
	}

	if (strcmp(my_event1->name, my_event2->name) == EQUAL
		&& dateCompare((my_event1->date), (my_event2->date)) == EQUAL)
	{
		return true;
	}

	return false;
}

void setEventDate(Event my_event, Date date)
{
	if (my_event != NULL)
	{
		my_event->date = date;
	}
}

void setEventId(Event my_event, int id)
{
	if (my_event != NULL)
	{
		my_event->id = id;
	}
}

void setEventName(Event my_event, char* name)
{
	if (my_event != NULL)
	{
		my_event->name = name;
	}
}

Date getEventDate(Event my_event)
{
	if (my_event == NULL)
	{
		return NULL;
	}

	return my_event ->date;
}

int getEventId(Event my_event)
{
	if (my_event == NULL)
	{
		return -1;
	}

	return my_event->id;
}

char* getEventName(Event my_event)
{
	if (my_event == NULL)
	{
		return NULL;
	}

	return my_event->name;
}

PriorityQueue getEventAssociation(Event my_event)
{
	if (my_event == NULL)
	{
		return NULL;
	}

	return my_event->event_association_members;
}