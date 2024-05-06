#ifndef event_container_h
#define event_container_h

#include "base_event.h"

namespace mtm
{
    class EventContainer
    {
    protected:
        List<BaseEvent*> EventList;
    public:
        EventContainer();
        /*destructor*/
        virtual ~EventContainer();
        EventContainer& operator=(const EventContainer&)=delete;
        EventContainer(const EventContainer& event_container)=delete;
        virtual void add(const BaseEvent& event) = 0;

        /**
        * sortByDate: sorts an events list by date in an ascending oreder
        */
        void sortByDate();

        /**
         * sort: second-sorts a list of events that is sorted by dates by their name in a lexicographic order
        */
        virtual void sort();
        
        class EventIterator;
        EventIterator begin();
        EventIterator end();
        
        /*class for implementing constant iterator*/
        class ConstEventIterator;
        ConstEventIterator begin() const;
        ConstEventIterator end() const;
    };

    class EventContainer::EventIterator
    {
        friend class EventContainer;
        EventContainer* current_container;
        Node<BaseEvent*>* index;
        EventIterator(EventContainer* event_conatiner, Node<BaseEvent*>* index);

    public:
        EventIterator(const EventIterator& iterator);
        virtual ~EventIterator() = default;
        mtm::BaseEvent& operator*() const;
        EventIterator& operator++();
        EventIterator& operator=(EventIterator const& iterator) = default;
        bool operator!=(const EventIterator& iterator) const;
        bool operator==(const EventIterator& iterator) const;

    };
class EventContainer::ConstEventIterator
{
    friend class EventContainer;
    const EventContainer* current_container;
    Node<BaseEvent*>* index;
    ConstEventIterator(const EventContainer* event_container, Node<BaseEvent*>* index);

public:
    ConstEventIterator(const ConstEventIterator& iterator);
    virtual ~ConstEventIterator() = default;
    const mtm::BaseEvent& operator*() const;
    ConstEventIterator& operator++();
    ConstEventIterator& operator=(const ConstEventIterator& iterator) = default;
    bool operator!=(const ConstEventIterator& iterator) const;
    bool operator==(const ConstEventIterator& iterator) const;

};
}
#endif /* event_container_h */
