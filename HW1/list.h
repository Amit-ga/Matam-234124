#ifndef List_H_
#define List_H_

#include <stdbool.h>

/**
*
* Generic List Container
* Implements a list container type.
* each node in the list has a next value pointing at the next node on the list
*the last node's next value is NULL.
*
* The following functions are available:
*   nodeCopy        - Copies an existing node
*   nodeCreate		- Creates a new empty node
*   nodeDestroy		- Deletes an specific node ont the list and frees all it's resources
*   listCreate		- Creates a new empty list
*   listDestroy		- Deletes an existing list and frees all resources
*   listCopy		- Copies an existing list
*	listClear		- Clears the contents of the list.
*   setElement      - Sets the key of a given node.
*	setPriority     - Sets the value of a given node.
*	setNextIndex    - Sets the next pointer of a given node.
*	getElement      - Returns the element associated with a specific node in the list(not a copy).
*	getPriority     - Returns the priority associated with a specific node in the list(not a copy).
*	getNextIndex    - returns the next node on the list
*	getHead         - returns the head of a given list
*	setHead         - Sets the head of a list to a given node.
*/

/** Type used for returning error codes from list functions */
typedef enum listResult_t {
	LIST_SUCCESS,
	LIST_OUT_OF_MEMORY,
	LIST_NULL_ARGUMENT,
	LIST_ERROR
} listResult;

/** element data type for list container */
typedef void* ListElement;

/** priority data type for list container */
typedef void* ListElementPriority;

/** Type of function for copying a data element of the list */
typedef ListElement(*CopyListElement)(ListElement);

/** Type of function for copying a key element of the list */
typedef ListElementPriority(*CopyListElementPriority)(ListElementPriority);

/** Type of function for deallocating a data element of the list */
typedef void(*FreeListElement)(ListElement);

/** Type of function for deallocating a key element of the list */
typedef void(*FreeListElementPriority)(ListElementPriority);

/**
* Type of function used by the list to identify equal elements.
* This function should return:
* 		true if they're equal;
*		false otherwise;
*/
typedef bool(*EqualListElements)(ListElement, ListElement);

/**
* Type of function used by the list to compare priorities.
* This function should return:
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/

typedef int(*CompareListElementPriorities)(ListElementPriority, ListElementPriority);

/** Type for defining a node */
typedef struct Node_t* Node;

/** Type for defining a list */
typedef struct list_t* List;

/**
* nodeCopy: Creates a copy of target node.
*
* @param node - Target node.
* @param copy_element - copying function for element
* @param free_element - freeing function for 
* @param copy_priority - copying function for priority
* @param free_priority - freeing function for priority
* @return
* 	NULL if a NULL was sent, or a memory allocation failed.
* 	A node containing the same elements as node param otherwise.
*/
Node nodeCopy(Node node, CopyListElement copy_element, CopyListElementPriority copy_priority,
	FreeListElement free_element, FreeListElementPriority free_priority);

/**
* nodeCreate: Allocates a new empty node.
* @return
* 	NULL - if allocations failed.
* 	A new node in case of success.
*/
Node nodeCreate();

/**
* nodeDestroy: Deallocates an existing node . Clears all elements by using the free functions.
*
* @param head - Target node  to be deallocated, free functions. If node  is NULL nothing will be done
* @param free_element - freeing function for 
* @param free_priority - freeing function for priority
*/
void nodeDestroy(Node head, FreeListElement free_element, FreeListElementPriority free_priority);

/**
* listCreate: Allocates a new empty list.
* @param copy_element - copying function for element
* @param free_element - freeing function for
* @param equal_elements - comparing function for element
* @param copy_priority - copying function for priority
* @param free_priority - freeing function for priority
* @param compare_priorities - comparing function for priority
* @return
* 	NULL - if allocations failed.
* 	A new list in case of success.
*/
List listCreate(CopyListElement copy_element,
	FreeListElement free_element,
	EqualListElements equal_elements,
	CopyListElementPriority copy_priority,
	FreeListElementPriority free_priority,
	CompareListElementPriorities compare_priorities);

/**
* listDestroy: Deallocates an existing list . Clears all elements by using the free functions.
*
* @param list - Target list  to be deallocated. If list is NULL nothing will be done
* 
*/
void listDestroy(List list);


/**
* listCopy: Creates a copy of target list.
*
* @param head - Pointer to the first node of target list.
* @param copy_element - copying function for element
* @param free_element - freeing function for 
* @param equal_elements - comparing function for element
* @param copy_priority - copying function for priority
* @param free_priority - freeing function for priority
* @param compare_priorities - comparing function for priority
* @return
* 	NULL if a NULL was sent, or a memory allocation failed.
* 	A node pointer to the beginnig of a list containing the same elements as list otherwise.
*
* */

List listCopy(Node head, CopyListElement copy_element,
	FreeListElement free_element,
	EqualListElements equal_elements,
	CopyListElementPriority copy_priority,
	FreeListElementPriority free_priority,
	CompareListElementPriorities compare_priorities);

/*
*listClear: Removes all elements and priorities from target  list.
* The elements are deallocated using the stored free functions.
* @param queue
* Target list to remove all element from.
*/
void listClear(List list);

/**
*	setElement: Sets the key of a given node.
*
* @param node - The node for which to assign the data element
* @param element - The key element which needs to be assigned.
*                   A copy of the key element will be inserted.
* @param copy_element - copying function for element
* @return
* 	LIST_NULL_ARGUMENT if one of the params is NULL
* 	LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	LIST_SUCCESS the element had been inserted successfully
*/
listResult setElement(CopyListElement copy_element, Node node, void* element);

/**
*	setPriority: Sets the value of a given node.
*
* @param node - The node for which to assign the priority
* @param priority - The value which needs to be assigned.
*                 A copy of the priority will be inserted.
* @param copy_priority- copying function for priority
* @return
* 	LIST_NULL_ARGUMENT if one of the params is NULL
* 	LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	LIST_SUCCESS the element had been inserted successfully
*/
listResult setPriority(CopyListElementPriority copy_priority , Node node, void* priority);

/**
*	setNextIndex: Sets the next pointer of a given node.
*
* @param node - The node for which to assign the pointer
* @param next - The node pointer which needs to be assigned.
*
* @return
* 	LIST_NULL_ARGUMENT if one of the params is NULL
* 	LIST_SUCCESS the element had been inserted successfully
*/
listResult setNextIndex(Node node, Node next);

/**
*	getElement: Returns the element associated with a specific node in the list(not a copy).
*
* @param node - The node for which to get the key element from.
*
* @return
*  NULL if a NULL pointer was sent.
*  A pointer to the key element associated with the node otherwise.
*/
void* getElement(Node node);

/**
*	getPriority: Returns the priority associated with a specific node in the list(not a copy).
*
* @param node - The node for which to get the value element from.
*
* @return
*  NULL if a NULL pointer was sent.
*  A pointer to the value element associated with the node otherwise.
*/
void* getPriority(Node node);

/**
*	getNextIndex: returns the next node on the list
*
* @param node - The node of which to get the next pointer
* @return
* 	NULL if reached the end of the list, or a NULL sent as argument
* 	The next node on the list in case of success
*/
Node getNextIndex(Node node);

/**
*	getHead: returns the head of a given list
*
* @param list - The list of which to get the head
* @return
* 	NULL if NULL was sent or list id empty
* 	The list's head in case of success
*/
Node getHead(List list);

/**
*	setHead: Sets the head of a list to a given node.
*
* @param list - The list for which to assign the new head
* @param to_assign - The node pointer which needs to be assigned.
*
* @return
* 	LIST_NULL_ARGUMENT if one of the params is NULL
* 	LIST_SUCCESS if the head had been ad=ssigned successfully
*/
listResult setHead(List list, Node to_assign);

#endif //List_H

