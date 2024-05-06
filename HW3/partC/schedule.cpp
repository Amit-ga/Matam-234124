#include <vector>
#include <algorithm>
#include "schedule.h"
#include "exceptions.h"

/*static functions declaration*/
namespace mtm
{

/**
* getEvent: returns A pointer that occures on a given date and has a given name
*
* @param date - Target event date
* @param name - Target event name
* @param events - Target vector of events to be searched in
* @return
* 	a pointer to the event that matches the given name and date
* 	Null if a matching event doesnt exist
*/
	static BaseEvent* getEvent(const mtm::DateWrap& date, const std::string& name, const std::vector<mtm::BaseEvent*>& events);


/**
* mySortingFunction: compares 2 events
*
* @param event1 - First target event to be compared
* @param event2 - Second target event to be compared
* @return
*	true if be1 occures before be2
* 	false otherwise
*/
	static bool mySortingFunction(mtm::BaseEvent* event1, mtm::BaseEvent* event2);

}


/*end of static functions declaration*/

/*static functions implementation*/

static mtm::BaseEvent* mtm::getEvent(const mtm::DateWrap& date, const std::string& name, const std::vector<mtm::BaseEvent*>& events)
{
    for (auto iterator = events.begin(); iterator != events.end(); iterator++)
    {
        if ((*(*iterator)).date() == date && (*(*iterator)).name() == name)
        {
            return (*iterator);
        }
    }
    return nullptr;
}

static bool mtm::mySortingFunction(mtm::BaseEvent* event1, mtm::BaseEvent* event2)
{
    if (event1->date() <= event2->date())
    {
        if (event1->date() < event2->date())
        {
            return true;
        }
        else
        {
            if (event1->name() < event2->name())
            {
                return true;
            }
        }
    }
    return false;

}

/*end of static functions implementation*/

mtm::Schedule::Schedule():
    events(std::vector<mtm::BaseEvent*>())
{
}

mtm::Schedule::~Schedule()
{
    for (std::vector<mtm::BaseEvent*>::const_iterator iterator = this->events.cbegin(); iterator != this->events.cend(); ++iterator)
    {
        delete *iterator;
        
    }

}
void mtm::Schedule::addEvents(const mtm::EventContainer& event_container)
{
	//check if event already exists
	for (mtm::EventContainer::ConstEventIterator external_iterator = event_container.begin(); external_iterator != event_container.end(); ++external_iterator)
	{
		for (std::vector<mtm::BaseEvent*>::const_iterator internal_iterator = this->events.cbegin(); internal_iterator != this->events.cend(); ++internal_iterator)
		{
			if ((*(*internal_iterator)) == *external_iterator)
			{
				throw mtm::EventAlreadyExists();
			}
		}
	}

	for (mtm::EventContainer::ConstEventIterator iterator = event_container.begin(); iterator != event_container.end(); ++iterator)
	{
		this->events.push_back((*iterator).clone());
	}

	std::sort(this->events.begin(), this->events.end(), mySortingFunction);
}

void mtm::Schedule::registerToEvent(const mtm::DateWrap& date, const std::string& name, int student)
{
	mtm::BaseEvent* event = getEvent(date, name,this->events);

	if (event==nullptr)
	{
		throw mtm::EventDoesNotExist();
	}
    
    event->registerParticipant(student);

}

void mtm::Schedule::unregisterFromEvent(const DateWrap& date, const std::string& name, int student)
{
	mtm::BaseEvent* event = getEvent(date, name, this->events);

	if (event == nullptr)
	{
		throw mtm::EventDoesNotExist();
	}

    event->unregisterParticipant(student);
}

void mtm::Schedule::printAllEvents() const
{
	for (auto iterator = this->events.begin(); iterator != this->events.end(); iterator++)
	{
		(*iterator)->printShort(std::cout);
		std::cout << "\n";
	}
}

void mtm::Schedule::printMonthEvents(int month, int year) const
{
	mtm::DateWrap min_date(mtm::min_day, month, year); //min date in month
	mtm::DateWrap max_date(mtm::max_day, month, year); //max date in month

	for (auto iterator = this->events.begin(); iterator != this->events.end(); iterator++)
	{
		if ((*iterator)->date() > max_date)
		{
			break;
		}
		else
		{
			if ((*iterator)->date() >= min_date)
			{
				(*iterator)->printShort(std::cout);
				std::cout << "\n";
			}
		}
	}
}

void mtm::Schedule::printEventDetails(const mtm::DateWrap& date, const std::string& name) const
{
	mtm::BaseEvent* event = getEvent(date, name, this->events);
		if (event == nullptr)
		{
			throw mtm::EventDoesNotExist();
		}
		else
		{
            event->printLong(std::cout);
            std::cout << "\n";
		}
}
