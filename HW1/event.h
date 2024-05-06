#ifndef EVENT_H_
#define EVENT_H_

#include "date.h"
#include "priority_queue.h"

/**
* EVENT ADT
*
* Implements an event data type.
* each event has a name (type char*), a date of occurrence (type Date), 
   a unique id (type int) and a queue of association_members (type priority queue),/
   in that priority queue, the element is type student and the priority is the student's id.
*
* The following functions are available:
*   eventCreate		                    - Creates a new empty event
*   eventDestroy		                - Deletes an existing event and frees all resources
*   eventCopy		                    - Copies an existing event
*   equalEvents  	                    - identifies equal events by their id
*   equalElementsDateAndName	        - identifies equal events by their name and date
*	setEventDate                        - Sets the event date to a given date.
*   setEventId                          - Sets the event id to a given id.
*   setEventName                        - Sets the event name to a given name.
*   getEventDate                        - returns the date of a given event
*	getEventId                          -returns the id of a given event
*	getEventName                        - returns the name of a given event
*	getEventAssociation                 - returns the association members of a given event
* 
*/

/** Type for defining the content of the event */
typedef struct Event_t* Event;

/**
* eventCreate: Allocates a new empty event.
*
* @return
* 	NULL - if allocations failed.
* 	A new event in case of success.
*/
Event eventCreate();

/**
* eventDestroy: Deallocates an existing event. frees all elements.
*
* @param my_event - Target event to be deallocated. If event is NULL nothing will be done
*/
void eventDestroy(Event my_event);

/**
* eventCopy: Creates a copy of target event.
* 
* @param my_event - Target event.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A new event the same as e otherwise.
*/
Event eventCopy(Event my_event);

/**
* equalEvents: identifies equal events by their id.
*
* @param my_event1 - first target event to be compared
* @param my_event2 - second target event to be compared.
* @return
* 		false if the 2 events don't have the same id or one of them is NULL
* 		true if the 2 events have the same id
*/
bool equalEvents(Event my_event1, Event my_event2);

/**
* equalElementsDateAndName: identifies equal events by their name and date.
*
* @param my_event1 - first target event to be compared
* @param my_event2 - second target event to be compared.
* @return
* 		false if the 2 events don't have the same name and the same id or one of them is NULL
* 		true if the 2 events have the same name and the same id
*/
bool equalElementsDateAndName(Event my_event1, Event my_event2);

/**
*	setEventDate: Sets the event date to a given date.
*
* @param my_event - The event for which to assign the new date
* @param date - The new date which needs to be assigned.
*
*/
void setEventDate(Event my_event, Date date);

/**
*	setEventId: Sets the event id to a given id.
*
* @param my_event - The event for which to assign the new id
* @param id - The new id which needs to be assigned.
*
*/
void setEventId(Event my_event, int id);

/**
*	setEventName: Sets the event name to a given name.
*
* @param my_event - The event for which to assign the new name
* @param name - The new name which needs to be assigned.
*
*/
void setEventName(Event my_event, char* name);


/**
*	getEventDate: returns the date of a given event
*
* @param my_event - The event of which to get the date
* @return
* 	NULL if NULL was sent or event date is NULL
* 	The event's date in case of success
*/
Date getEventDate(Event my_event);

/**
*	getEventId: returns the id of a given event
*
* @param my_event - The event of which to get the id
* @return
* 	NULL if NULL was sent 
* 	The event's id in case of success
*/
int getEventId(Event my_event);

/**
*	getEventName: returns the name of a given event
*
* @param my_event - The event of which to get the name
* @return
* 	NULL if NULL was sent or event name is NULL
* 	The event's name in case of success
*/
char* getEventName(Event my_event);

/**
*	getEventAssociation: returns the association members of a given event
*
* @param my_event - The event of which to get the association members
* @return
* 	NULL if NULL was sent or event association members is NULL
* 	The event's association members in case of success
*/
PriorityQueue getEventAssociation(Event my_event);

#endif //Event_H_



