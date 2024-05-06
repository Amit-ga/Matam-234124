#include "priority_queue.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct PriorityQueue_t {

	List list;
	int queue_size;
	Node iterator;

	//functions pointers
	CopyPQElement copy_element;
	FreePQElement free_element;
	EqualPQElements equal_elements;
	CopyPQElementPriority copy_priority;
	FreePQElementPriority free_priority;
	ComparePQElementPriorities compare_priorities;

};


PriorityQueue pqCreate(CopyPQElement copy_element,
	FreePQElement free_element,
	EqualPQElements equal_elements,
	CopyPQElementPriority copy_priority,
	FreePQElementPriority free_priority,
	ComparePQElementPriorities compare_priorities)
{
	if (!copy_element || !free_element || !equal_elements
		|| !copy_priority || !free_priority || !compare_priorities)
	{
		return NULL;
	}

	PriorityQueue pq = malloc(sizeof(*pq));
	if (pq == NULL)
	{
		return NULL;
	}


	pq->copy_element = copy_element;
	pq->free_element = free_element;
	pq->equal_elements = equal_elements;
	pq->copy_priority = copy_priority;
	pq->free_priority = free_priority;
	pq->compare_priorities = compare_priorities;


	pq->list = listCreate(copy_element,free_element,equal_elements,copy_priority, free_priority,compare_priorities);

	if (pq->list == NULL)
	{
		pqDestroy(pq);
		return NULL;
	}

	pq->iterator = NULL;
	pq->queue_size = 0;
	return pq;

}

void pqDestroy(PriorityQueue queue)
{
	listDestroy(queue->list);
	free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue)
{

	if (queue == NULL)
	{
		return NULL;
	}

	queue->iterator = NULL;

	PriorityQueue new_pq = pqCreate(queue->copy_element, queue->free_element,
		queue->equal_elements, queue->copy_priority
		, queue->free_priority, queue->compare_priorities);

	if (new_pq == NULL )
	{
		return NULL;
	}

	listDestroy(new_pq->list);

	assert(queue->list != NULL);

		assert(queue->list != NULL);
		List new_list = listCopy(getHead(queue->list), queue->copy_element, queue->free_element,
			queue->equal_elements, queue->copy_priority
			, queue->free_priority, queue->compare_priorities);
		if (new_list == NULL)
		{
			pqDestroy(new_pq);
			return NULL;
		}

		new_pq->list = new_list;

	//both iterators are undefined
	assert(new_pq != NULL);
	new_pq->iterator = NULL;
	new_pq->queue_size = queue->queue_size;
	return new_pq;
}

int pqGetSize(PriorityQueue queue)
{
	if (queue == NULL)
	{
		return -1;
	}

	return queue->queue_size;
}

bool pqContains(PriorityQueue queue, PQElement element)
{

	if (queue == NULL || element == NULL)
	{
		return false;
	}

	Node temp = getHead(queue->list);
	while (temp)
	{
		if (queue->equal_elements(getElement(temp), element))
		{
			return true;
		}
		else
		{
			temp = getNextIndex(temp);
		}
	}

	return false;
}

PriorityQueueResult pqInsert(PriorityQueue queue, PQElement element, PQElementPriority priority)
{

	if (queue == NULL || element == NULL || priority == NULL)
	{
		return PQ_NULL_ARGUMENT;
	}

	queue->iterator = NULL;

	Node new_node = nodeCreate();
	{
		if (new_node == NULL)
		{
			return PQ_OUT_OF_MEMORY;
		}
	}

	listResult result = setElement(queue->copy_element, new_node, element);
	if (result!=LIST_SUCCESS)
	{
		nodeDestroy(new_node, queue->free_element, queue->free_priority);
		return PQ_OUT_OF_MEMORY;
	}

	result = setPriority(queue->copy_priority, new_node, priority);
	if (result != LIST_SUCCESS)
	{
		nodeDestroy(new_node, queue->free_element, queue->free_priority);
		return PQ_OUT_OF_MEMORY;
	}

	if (getHead(queue->list) == NULL)
	{
		setNextIndex(new_node, NULL);
		result= setHead(queue->list, new_node);
		assert(result != LIST_NULL_ARGUMENT);
	}

	else
	{
		Node left = NULL;
		Node right = getHead(queue->list);
		while (right)
		{
			if (queue->compare_priorities(getPriority(right), getPriority(new_node)) < 0)
			{
				setNextIndex(new_node, right);
				break;
			}
			else
			{
					left = right;
					right = getNextIndex(right);
					continue;
			}
		}
		if (left == NULL)
		{
			result=setHead(queue->list, new_node);
			assert(result != LIST_NULL_ARGUMENT);
		}
		else
		{
			setNextIndex(left, new_node);
		}
	}
	queue->queue_size++;
	return PQ_SUCCESS;
}

PriorityQueueResult pqChangePriority(PriorityQueue queue, PQElement element,
	PQElementPriority old_priority, PQElementPriority new_priority)
{

	if (queue == NULL || element == NULL || old_priority == NULL || new_priority == NULL)
	{
		return PQ_NULL_ARGUMENT;
	}

	queue->iterator = NULL;

	if (pqContains(queue, element) == false)
	{
		return PQ_ELEMENT_DOES_NOT_EXISTS;

	}
	Node temp = getHead(queue->list);
	while (temp)
	{
		if (queue->equal_elements(getElement(temp), element)
			&& queue->compare_priorities(getPriority(temp), old_priority) == 0)
		{
			break;
		}
		else
		{
			temp = getNextIndex(temp);
		}
	}

	if (temp == NULL)
	{
		return PQ_ELEMENT_DOES_NOT_EXISTS;
	}

	Node to_insert = nodeCopy(temp, queue->copy_element, queue->copy_priority, queue->free_element, queue->free_priority);
	if (to_insert == NULL)
	{
		return PQ_OUT_OF_MEMORY;
	}
	pqRemoveElement(queue, getElement(temp));
	assert(queue != NULL && new_priority != NULL && getElement(to_insert) != NULL);
	PriorityQueueResult result = pqInsert(queue, getElement(to_insert), new_priority);
	assert(result == PQ_SUCCESS || result == PQ_OUT_OF_MEMORY);
	nodeDestroy(to_insert, queue->free_element, queue->free_priority);

	return result;
}

PriorityQueueResult pqRemove(PriorityQueue queue)
{
	if (queue == NULL )
	{
		return PQ_NULL_ARGUMENT;
	}

	queue->iterator = NULL;

	if (queue->list == NULL || getHead(queue->list)==NULL)
	{
		return PQ_SUCCESS;
	}
	Node temp = getHead(queue->list);

	//by our implementaion the first element is always the highest priority element , and the first one that was inserted
	setHead(queue->list,getNextIndex(temp));
	setNextIndex(temp, NULL);
	nodeDestroy(temp, queue->free_element, queue->free_priority);

	queue->queue_size--;
	return PQ_SUCCESS;
}

PriorityQueueResult pqRemoveElement(PriorityQueue queue, PQElement element)
{
	if (queue == NULL || element == NULL)
	{
		return PQ_NULL_ARGUMENT;
	}

	queue->iterator = NULL;

	if (queue->list==NULL || pqContains(queue, element) == false)
	{
		return PQ_ELEMENT_DOES_NOT_EXISTS;
	}

	Node temp_iterator = getHead(queue->list);
	assert(temp_iterator != NULL);

	if (getNextIndex(temp_iterator) == NULL)
	{
		nodeDestroy(temp_iterator, queue->free_element, queue->free_priority);
		queue->queue_size--;
		setHead(queue->list, NULL);
		return PQ_SUCCESS;
	}

	Node prev = temp_iterator;
	temp_iterator = getNextIndex(temp_iterator);

	if (queue->equal_elements(getElement(prev), element) == true)
	{
		temp_iterator = prev;
	}
	
	else
	{
		//get to the first inserted element with highest priority
		while (temp_iterator)
		{
			if (queue->equal_elements(getElement(temp_iterator), element) == true)
			{
				break;
			}
			prev = temp_iterator;
			temp_iterator = getNextIndex(temp_iterator);
		}
	}

	if (getNextIndex(temp_iterator) == NULL)
	{
		setNextIndex(prev, NULL);
	}
	else
	{
		assert(prev && temp_iterator);
		setNextIndex(prev, getNextIndex(temp_iterator));
		if (temp_iterator == prev )
		{
			setHead(queue->list,getNextIndex(getHead(queue->list)));
		}

		setNextIndex(temp_iterator, NULL);
	}

	nodeDestroy(temp_iterator, queue->free_element, queue->free_priority);

	queue->queue_size--;
	return PQ_SUCCESS;
}

PQElement pqGetFirst(PriorityQueue queue)
{
	if (queue == NULL || queue->list == NULL|| getHead(queue->list)==NULL)
	{
		return NULL;
	}
	queue->iterator = getHead(queue->list);
	return getElement(queue->iterator);
}

PQElement pqGetNext(PriorityQueue queue)
{
	if (queue->iterator == NULL || queue->list==NULL || getHead(queue->list) == NULL)
	{
		return NULL;
	}
	
	Node temp = queue->iterator;

	//reached the end of the priority queue
	if (getNextIndex(temp)== NULL)
	{
		return NULL;
	}
	queue->iterator = getNextIndex(temp);
	return getElement(queue->iterator);
}

PriorityQueueResult pqClear(PriorityQueue queue)
{
	if (queue == NULL)
	{
		return PQ_NULL_ARGUMENT;
	}

	listClear(queue->list);
	setHead(queue->list, NULL);
	queue->iterator = NULL;
	queue->queue_size = 0;
	return PQ_SUCCESS;
}
