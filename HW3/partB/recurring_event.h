#ifndef RECURRING_EVENT_H
#define RECURRING_EVENT_H

#include "event_container.h"
#include "date_wrap.h"
#include "exceptions.h"

namespace mtm
{
	template<class EventType>
	class RecurringEvent : public EventContainer
	{

	public:
		RecurringEvent(DateWrap date_first, const std::string& name, int occurrences_num, int days_interval);
		void add(const BaseEvent& event) override;
		/*destructor*/
		virtual ~RecurringEvent() = default;

	};

	template<class EventType>
	mtm::RecurringEvent<EventType>::RecurringEvent(DateWrap first_date, const std::string& name, int num_occurrences, int interval_days)
	{
		if (num_occurrences <= 0)
		{
			throw mtm::InvalidNumber();
		}
		if (interval_days <= 0)
		{
			throw mtm::InvalidInterval();
		}
		for (int i = 0; i < num_occurrences; i++)
		{
            mtm::BaseEvent* temp= new EventType(first_date, name);
            this->EventList.addNode(temp);
            
			first_date += interval_days;
		}
	}

	template<class EventType>
	void mtm::RecurringEvent< EventType>::add(const BaseEvent& event)
	{
		throw mtm::NotSupported();
	}
}

#endif //RECURRING_EVENT_H
