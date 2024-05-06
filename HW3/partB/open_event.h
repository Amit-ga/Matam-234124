#ifndef open_event_h
#define open_event_h

#include "base_event.h"

namespace mtm {

    class OpenEvent : public BaseEvent {

    public:
        OpenEvent(const DateWrap& date, const std::string& name);
        virtual BaseEvent* clone() const override;
        /*destructor*/
        virtual ~OpenEvent() = default;
    };
}
#endif /* open_event_h */
