#ifndef custom_event_h
#define custom_event_h

#include "base_event.h"
#include "exceptions.h"

namespace mtm {

    template <class CanRegister>
    class CustomEvent : public BaseEvent {

        CanRegister is_allowed;

    public:
        CustomEvent(const DateWrap& date, const std::string& name, CanRegister my_function_object);
        void registerParticipant(int student_id) override;
        virtual BaseEvent* clone() const override;
        /*destructor*/
        virtual ~CustomEvent() = default;

    };

    template <class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const DateWrap& date, const std::string& name, CanRegister my_function_object) :
        BaseEvent(date, name),
        is_allowed(my_function_object)
    {

    }

    template <class CanRegister>
    void mtm::CustomEvent< CanRegister>::registerParticipant(int student_id)
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
            if (this->is_allowed(student_id))
            {
                this->guests_list.addNode(student_id);
            }
            else
            {
                throw mtm::RegistrationBlocked();
            }
        }
    }

    template <class CanRegister>
    mtm::BaseEvent* mtm::CustomEvent<CanRegister>::clone() const
    {
        return new CustomEvent<CanRegister>(*this);
    }
}

#endif /* custom_event_h */
