#include <iostream>
#include <string>
#include "base_event.h"
#include "date_wrap.h"
#include "exceptions.h"

/*static functions declaration*/

namespace mtm

{ 
    /**
    * findMin: get the minimal number in the list, that is greater than min
    *
    * @param list - target list to find min value in
    * @param min - lowest bound
    * @return
    * The first higher than min number in the list
    */
    static int findMin(const List<int>& list, int min);
}

/*end of static functions declaration*/


/*static functions implementation*/

static int mtm::findMin(const mtm::List<int>& list, int min)
{
    int max = max_student_id;
    mtm::Node<int>* tmp = list.getHead();
    while (tmp)
    {
        if (tmp->value() > min && tmp->value() < max)
        {
            max = tmp->value();
        }
        tmp = tmp->next();
    }
    return max;
}

/*end of static functions implementation*/

mtm::BaseEvent::BaseEvent(const mtm::DateWrap& date, const std::string& event_name) :
    event_date(date.day(), date.month(), date.year()),
    event_name(event_name),
    guests_list(List<int>())
{
}

mtm::BaseEvent::BaseEvent(const BaseEvent& base_event) :
    event_date(base_event.event_date),
    event_name(base_event.event_name),
    guests_list(List<int>(base_event.guests_list))
{
}

void mtm::BaseEvent::registerParticipant(int student_id)
{
    if (student_id <mtm::min_student_id || student_id > mtm::max_student_id)
    {
        throw mtm::InvalidStudent();
    }

    if (this->guests_list.contains(student_id))
    {
        throw mtm::AlreadyRegistered();
    }
    else
    {
        this->guests_list.addNode(student_id);
    }
}

void mtm::BaseEvent::unregisterParticipant(int student_id)
{
    if (student_id < mtm::min_student_id || student_id > mtm::max_student_id)
    {
        throw mtm::InvalidStudent();
    }

    if (!(this->guests_list.deleteNode(student_id)))
    {
        throw mtm::NotRegistered();
    }
}

std::ostream& mtm::BaseEvent::printShort(std::ostream& os)
{
    return printShortOrLong(os, false);
}

std::ostream& mtm::BaseEvent::printLong(std::ostream& os)
{
    return printShortOrLong(os, true);
}

bool mtm::BaseEvent::operator==(const BaseEvent& base_event) const
{
    if (this->date() == base_event.date() && this->name() == base_event.name())
    {
        return true;
    }

    return false;
}

std::ostream& mtm::BaseEvent::printShortOrLong(std::ostream& os, bool isLongPrint)
{
    std::string members = "";
    if (isLongPrint)
    {
        orderGuestList();
        mtm::Node<int>* iterator = this->guests_list.getHead();
        for (int i = 0; i < this->guests_list.getSize(); i++)
        {
            members += std::to_string(iterator->value());
            members += "\n";
            iterator = iterator->next();
        }
    }
    return os << this->event_name << " " << this->event_date << "\n" << members;
}

void mtm::BaseEvent::orderGuestList()
{
    List<int> ordered_list = List<int>();
    if(!(this->guests_list.getSize()))
    {
        return;
    }
    while (ordered_list.getSize() != this->guests_list.getSize())
    {
        int last_student = (ordered_list.getSize() != 0) ? ordered_list.getLastValue() : 0;
        int value = findMin(this->guests_list, last_student);
        ordered_list.addNode(value);
    }
    this->guests_list = List<int>(ordered_list);
}

mtm::DateWrap mtm::BaseEvent::date() const
{
    return this->event_date;
}
std::string mtm::BaseEvent::name() const
{
    return this->event_name;
}
