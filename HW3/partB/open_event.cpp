#include "open_event.h"

mtm::OpenEvent::OpenEvent(const mtm::DateWrap& date, const std::string& name) :
    mtm::BaseEvent(date, name)
{
}

mtm::BaseEvent* mtm::OpenEvent::clone() const
{
    return new mtm::OpenEvent(*this);
}
