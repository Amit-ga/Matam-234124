#ifndef ONE_TIME_EVENT_H
#define ONE_TIME_EVENT_H

#include "event_container.h"
#include "date_wrap.h"
#include"exceptions.h"

namespace mtm
{
	template <class EventType>
	class OneTimeEvent : public EventContainer
	{
	public:
		OneTimeEvent(const DateWrap& date, const std::string& name);
		void add(const BaseEvent& event) override;
		/*destructor*/
		virtual ~OneTimeEvent() = default;
	};

	template <class EventType>
	mtm::OneTimeEvent<EventType>::OneTimeEvent(const DateWrap& date, const std::string& name)
	{
        mtm::BaseEvent* temp=new EventType(date, name);
		this->EventList.addNode(temp);
	}

	template <class EventType>
	void mtm::OneTimeEvent<EventType>::add(const BaseEvent& event)
	{
		throw mtm::NotSupported();
	}

}

#endif //ONE_TIME_EVENT_H
