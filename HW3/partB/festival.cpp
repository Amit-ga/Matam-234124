#include "festival.h"
#include "exceptions.h"

mtm::Festival::Festival(mtm::DateWrap date) :
	mtm::EventContainer(),
	event_date(date)
{
}

void mtm::Festival::add(const BaseEvent& event)
{
	if (event.date() != this->event_date)
	{
		throw mtm::DateMismatch();
	}
    
	this->EventList.addNode(event.clone());
    
	sort();
}

