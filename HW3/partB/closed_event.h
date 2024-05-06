#ifndef closed_event_h
#define closed_event_h

#include "base_event.h"

namespace mtm {

    class ClosedEvent : public BaseEvent {

    private:
        List<int> Attendees;
    public:
        ClosedEvent(const DateWrap& date, const std::string& name);
        void addInvitee(int student);
        void registerParticipant(int student_id) override;
        virtual BaseEvent* clone() const override;
        /*destructor*/
        virtual ~ClosedEvent() = default;
    };
}
#endif /* close_event_h */
