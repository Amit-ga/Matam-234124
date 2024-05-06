#ifndef schedule_H
#define schedule_H

#include <vector>
#include "date_wrap.h"
#include "base_event.h"
#include "event_container.h"

namespace mtm
{
	class Schedule
	{
		std::vector<mtm::BaseEvent*> events;

	public:
		Schedule();
        ~Schedule();
		void addEvents(const EventContainer& event_container);
		void registerToEvent(const DateWrap& date, const std::string& name, int student);
		void unregisterFromEvent(const DateWrap& date, const std::string& name, int student);
		void printAllEvents() const;
		void printMonthEvents(int month, int year) const;
        
        void printEventDetails(const DateWrap& date, const std::string& name) const;

        template<class Predicate>
        void printSomeEvents(Predicate predicate, bool verbose=false) const;
		

	};

template<class Predicate>
void Schedule::printSomeEvents(Predicate predicate, bool verbose) const
{
    for (auto iterator = this->events.begin(); iterator != this->events.end(); iterator++)
    {
        if (predicate(*(*iterator)))
        {
            (*iterator)->printShortOrLong(std::cout, verbose);
            std::cout << "\n";
        }
    }
}

}

#endif //schedule_H
