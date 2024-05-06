#include <stdlib.h>
#include "list.h"

struct Node_t {

	void* element;
	void* priority;
	struct Node_t* next;

};

struct list_t  {

	Node head;

	CopyListElement copy_element;
	FreeListElement free_element;
	EqualListElements equal_elements;
	CopyListElementPriority copy_priority;
	FreeListElementPriority free_priority;
	CompareListElementPriorities compare_priorities;

};

List listCreate(CopyListElement copy_element,
	FreeListElement free_element,
	EqualListElements equal_elements,
	CopyListElementPriority copy_priority,
	FreeListElementPriority free_priority,
	CompareListElementPriorities compare_priorities)
{

	if (!copy_element || !free_element || !equal_elements
		|| !copy_priority || !free_priority || !compare_priorities)
	{
		return NULL;
	}

	List list = malloc(sizeof(*list));
	if (list == NULL)
	{
		return NULL;
	}


	list->copy_element = copy_element;
	list->free_element = free_element;
	list->equal_elements = equal_elements;
	list->copy_priority = copy_priority;
	list->free_priority = free_priority;
	list->compare_priorities = compare_priorities;


	list->head = NULL;
	
	return list;

}

Node nodeCopy(Node node, CopyListElement copy_element, CopyListElementPriority copy_priority,
	FreeListElement free_element, FreeListElementPriority free_priority)
{
	if (node == NULL)
	{
		return NULL;
	}

	Node new_node = nodeCreate();
	if (new_node != NULL)
	{
		void* new_element = copy_element(node->element);
		if (new_element == NULL)
		{
			nodeDestroy(new_node, free_element, free_priority);
			return NULL;
		}

		void* new_priority = copy_priority(node->priority);
		if (new_priority == NULL)
		{
			nodeDestroy(new_node, free_element, free_priority);
			free_element(new_element);
			return NULL;
		}

		new_node->element = new_element;
		new_node->priority = new_priority;
		new_node->next = NULL;
	}

	return new_node;
}

void nodeDestroy(Node head, FreeListElement free_element, FreeListElementPriority free_priority)
{
	while (head)
	{
		Node toDelete = head;
		head = head->next;
		free_element(toDelete->element);
		free_priority(toDelete->priority);
		free(toDelete);
	}
}

Node nodeCreate()
{
	Node node = malloc(sizeof(*node));
	if (node == NULL)
	{
		return NULL;
	}
	node->element = NULL;
	node->priority = NULL;
	node->next = NULL;

	return node;
}


void listDestroy(List list)
{
	listClear(list);
	free(list);
}


List listCopy(Node head , CopyListElement copy_element,
	FreeListElement free_element,
	EqualListElements equal_elements,
	CopyListElementPriority copy_priority,
	FreeListElementPriority free_priority,
	CompareListElementPriorities compare_priorities)
{
	List new_list = listCreate(copy_element, free_element, equal_elements, copy_priority, free_priority, compare_priorities);
	if (new_list == NULL)
	{
		return NULL;
	}

	if (head == NULL)
	{
		new_list->head = NULL;
		return new_list;
	}
	
	Node new_head = nodeCopy(head, copy_element,copy_priority,free_element,free_priority);
	if (new_head == NULL)
	{
		return NULL;
	}

	Node temp1 = head; //iterator for input node
	Node temp2 = new_head; //iterator for new list
	while (temp1->next != NULL)
	{
		temp2->next = nodeCopy(temp1->next, copy_element, copy_priority, free_element,free_priority);
		if (temp2->next==NULL)
		{
			nodeDestroy(new_head,free_element,free_priority);
			return NULL;
		}

		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	new_list->head = new_head;
	return new_list;
}

void listClear(List list)
{
	nodeDestroy(list->head, list->free_element, list->free_priority);
}

listResult setElement(CopyListElement copy_element, Node node, void* element)
{
	listResult result = LIST_SUCCESS;
	if (node == NULL || element == NULL || copy_element==NULL)
	{
		result = LIST_NULL_ARGUMENT;
		return result;
	}

	void* local_element = copy_element(element);
	if (local_element == NULL)
	{
		result = LIST_OUT_OF_MEMORY;
		return result;
	}
	node->element = local_element;
	return result;
}

listResult setPriority(CopyListElementPriority copy_priority, Node node, void* priority)
{
	listResult result = LIST_SUCCESS;
	if (node == NULL || priority == NULL || copy_priority==NULL)
	{
		result = LIST_NULL_ARGUMENT;
		return result;
	}

	//reset an existing value
	if (node->priority != NULL)
	{
		free(node->priority);
	}

	void* local_priority = copy_priority(priority);
	if (local_priority == NULL)
	{
		result = LIST_OUT_OF_MEMORY;
		return result;
	}

	node->priority = local_priority;
	return result;
}

listResult setNextIndex(Node node, Node next)
{
	listResult result = LIST_SUCCESS;

	if (node == NULL)
	{
		result = LIST_NULL_ARGUMENT;
		return result;
	}

	node->next = next;
	return result;
}

void* getElement(Node node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return node->element;
}

void* getPriority(Node node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return node->priority;
}

Node getNextIndex(Node node)
{
	if (node == NULL)
	{
		return NULL;
	}
	return node->next;
}

Node getHead(List list)
{
	if (list == NULL || list->head == NULL)
	{
		return NULL;
	}

	return list->head;
}

listResult setHead(List list, Node to_assign)
{
	if (list == NULL)
	{
		return LIST_NULL_ARGUMENT;
	}
	list->head = to_assign;
	return LIST_SUCCESS;
}