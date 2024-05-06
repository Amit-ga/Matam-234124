#include "closed_event.h"
#include "exceptions.h"

mtm::ClosedEvent::ClosedEvent(const mtm::DateWrap& date, const std::string& name) :
    mtm::BaseEvent(date, name),
    Attendees(List<int>())
{
}

void mtm::ClosedEvent::addInvitee(int student)
{
    if (student < mtm::min_student_id || student > mtm::max_student_id)
    {
        throw mtm::InvalidStudent();
    }
    if (Attendees.contains(student))
    {
        throw mtm::AlreadyInvited();
    }
    Attendees.addNode(student);
}

void mtm::ClosedEvent::registerParticipant(int student_id)
{
    if (student_id <mtm::min_student_id || student_id > mtm::max_student_id)
    {
        throw mtm::InvalidStudent();
    }

    if (this->guests_list.contains(student_id))
    {
        throw  mtm::AlreadyRegistered();
    }

    else
    {
        if (!(this->Attendees.contains(student_id)))
        {
            throw mtm::RegistrationBlocked();
        }

        else
        {
            this->guests_list.addNode(student_id);
        }
    }
}

mtm::BaseEvent* mtm::ClosedEvent::clone() const
{
    return new mtm::ClosedEvent(*this);
}
