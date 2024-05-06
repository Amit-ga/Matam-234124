#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include "date_wrap.h"
#include "list.h"

namespace mtm
{
    //const variables
    const int min_student_id = 1;
    const int max_student_id = 1234567890;

    class BaseEvent
    {
        DateWrap event_date;
        std::string event_name;

    protected:
        List<int> guests_list;

    public:
        BaseEvent(const DateWrap& date, const std::string& name);
        /*destructor*/
        virtual ~BaseEvent() = default;
        /*copy constructor*/
        BaseEvent& operator=(const BaseEvent&)=delete;
        BaseEvent(const BaseEvent& base_event);
        virtual void registerParticipant(int student_id);
        virtual void unregisterParticipant(int student_id);
        std::ostream& printShort(std::ostream& os);
        std::ostream& printLong(std::ostream& os);
        virtual BaseEvent* clone() const = 0;
        
        /**
        * operator ==:  compares 2 events
        *2 events are considered equals if they have the same date and the same name
        *
        * @param base_event -  second target event to be compared
        * @return
        *       true if the events are equal
        *       false otherwise
        */
        bool operator==(const BaseEvent& base_event) const;

        /**
        * printShortOrLong: returns A pointer that occures on a given date and has a given name
        *
        * @param os - target printing variable
        * @param isLongPrint - whether the printing is long print or not
        * @return
        * the suitable printing according to isLongPrint parameter
        */
        std::ostream& printShortOrLong(std::ostream& os, bool isLongPrint);

        /**
        * orderGuestList: sorts gusests list in an ascending order
        *
        */
        void orderGuestList();

        /**
        * date: get an event's date of uccurence.
        * @return
        * 	this's day data member
        */
        mtm::DateWrap date() const;

        /**
        * name: get an event's name
        * @return
        * 	this's month data member
        */
        std::string name() const;
    };
}

#endif//BASE_EVENT_H
