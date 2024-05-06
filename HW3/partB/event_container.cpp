#include "event_container.h"

/*static functions declaration*/

/*Helper function for sortByDate, swaps the nodes ptr1 and ptr2 during the sort*/
static mtm::Node<mtm::BaseEvent*>* swapToSort(mtm::Node<mtm::BaseEvent*>* ptr1, mtm::Node<mtm::BaseEvent*>* ptr2);

/*end of static functions declaration*/

/*static functions implementation*/

static mtm::Node<mtm::BaseEvent*>* swapToSort(mtm::Node<mtm::BaseEvent*>* ptr1, mtm::Node<mtm::BaseEvent*>* ptr2)
{
    mtm::Node<mtm::BaseEvent*>* tmp = ptr2->next();
    ptr2->setNext(ptr1);
    ptr1->setNext(tmp);
    return ptr2;
}

/*end of static functions implementation*/

mtm::EventContainer::EventContainer():
EventList(mtm::List<mtm::BaseEvent*>())
{
}

 mtm::EventContainer::~EventContainer()
{
    for (mtm::EventContainer::EventIterator itrerator= this->begin(); itrerator!=this->end(); ++itrerator)
    {
        delete itrerator.index->value();
    }
}

void mtm::EventContainer::sortByDate()
{
	mtm::Node<mtm::BaseEvent*>* temp = this->EventList.getHead();
	mtm::Node<mtm::BaseEvent*>** head = nullptr;
	int i, j, swapped;

	for (i = 0; i <= this->EventList.getSize(); i++)
	{

		head = &temp;
		swapped = false;

		for (j = 0; j < this->EventList.getSize() - i - 1; j++)
		{

			mtm::Node<mtm::BaseEvent*>* ptr1 = *head;
			mtm::Node<mtm::BaseEvent*>* ptr2 = ptr1->next();

			if (ptr1->value()->date() > ptr2->value()->date())
			{

				/* update the link after swapping */
				*head = swapToSort(ptr1, ptr2);
				swapped = true;
			}

			mtm::Node<mtm::BaseEvent*>* temp2 = (*head)->next();

			head = &(temp2);
		}

		/* break if after the loop there wernt any swaps */
		if (swapped == false)
			break;
	}

}

void mtm::EventContainer::sort()
{
	this->sortByDate();

	for (int i = 0; i < this->EventList.getSize() - 1; i++)
	{
		mtm::Node<mtm::BaseEvent*>* temp = this->EventList.getHead();

		for (int j = 0; j < this->EventList.getSize() - 1; j++)
		{
			if (temp->value()->date() == temp->next()->value()->date())
			{
				if (temp->value()->name() > temp->next()->value()->name())
				{
					this->EventList.swap(temp);
				}
			}

			temp = temp->next();
		}
	}

}

mtm::EventContainer::EventIterator mtm::EventContainer::begin()
{
	return mtm::EventContainer::EventIterator(this, this->EventList.getHead());
}

mtm::EventContainer::EventIterator mtm::EventContainer::end() 
{
	mtm::EventContainer::EventIterator iterator = mtm::EventContainer::EventIterator(this, this->EventList.getHead());
	while (iterator.index != nullptr)
	{
		++iterator;
	}

	return iterator;
}

mtm::EventContainer::ConstEventIterator mtm::EventContainer::begin() const
{
    return mtm::EventContainer::ConstEventIterator(this, this->EventList.getHead());
}

mtm::EventContainer::ConstEventIterator mtm::EventContainer::end() const
{
    mtm::EventContainer::ConstEventIterator iterator = mtm::EventContainer::ConstEventIterator(this, this->EventList.getHead());
    while (iterator.index != nullptr)
    {
        ++iterator;
    }

    return iterator;
}

//iterator implementation

mtm::EventContainer::EventIterator::EventIterator(mtm::EventContainer* event_container, mtm::Node<mtm::BaseEvent*>* index) :
	current_container(event_container),
	index(index)
{
}

mtm::EventContainer::EventIterator::EventIterator(const EventIterator& iterator):
    current_container(iterator.current_container),
    index(iterator.index)
{
}

mtm::BaseEvent& mtm::EventContainer::EventIterator::operator*() const
{
    return *(this->index->value());
}

mtm::EventContainer::EventIterator& mtm::EventContainer::EventIterator::operator++()
{
	index = index->next();
	return (*this);
}
bool mtm::EventContainer::EventIterator::operator!=(const mtm::EventContainer::EventIterator& iterator) const
{
	return this->index != iterator.index;
}

bool mtm::EventContainer::EventIterator::operator==(const mtm::EventContainer::EventIterator& iterator) const
{
	return !mtm::EventContainer::EventIterator::operator!=(iterator);
}

//const iterator implementation

mtm::EventContainer::ConstEventIterator::ConstEventIterator(const mtm::EventContainer* event_container, mtm::Node<mtm::BaseEvent*>* index) :
    current_container(event_container),
    index(index)
{
}

mtm::EventContainer::ConstEventIterator::ConstEventIterator(const ConstEventIterator& iterator):
    current_container(iterator.current_container),
    index(iterator.index)
{
}

const mtm::BaseEvent& mtm::EventContainer::ConstEventIterator::operator*() const
{
    return *(this->index->value());
}

mtm::EventContainer::ConstEventIterator& mtm::EventContainer::ConstEventIterator::operator++()
{
    index = index->next();
    return (*this);
}
bool mtm::EventContainer::ConstEventIterator::operator!=(const mtm::EventContainer::ConstEventIterator& iterator) const
{
    return this->index != iterator.index;
}

bool mtm::EventContainer::ConstEventIterator::operator==(const mtm::EventContainer::ConstEventIterator& iterator) const
{
    return !mtm::EventContainer::ConstEventIterator::operator!=(iterator);
}

