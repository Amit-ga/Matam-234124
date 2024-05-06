#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace mtm
{
    class Exception : public std::exception {};

    //PART A
    /*Date exception*/
    class InvalidDate : public mtm::Exception
    {
    public:
        virtual const char* what() const noexcept;
    };

    class NegativeDays :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    //PART B
    /*Event exception*/
    class InvalidStudent : public Exception
    {
    public:
        const char* what()  const noexcept override;
    };

    class AlreadyRegistered :public Exception
    {
    public:
        const char* what()  const noexcept override;
    };

    class RegistrationBlocked :public Exception {
    public:
        const char* what() const noexcept override;
    };

    class NotRegistered :public Exception {
    public:
        const char* what() const noexcept override;
    };

    class AlreadyInvited :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    class NotSupported :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    class DateMismatch :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    class InvalidNumber :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    class InvalidInterval :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    //PART C

    class EventAlreadyExists :public Exception
    {
    public:
        const char* what() const noexcept override;
    };

    class EventDoesNotExist :public Exception
    {
    public:
        const char* what() const noexcept override;
    };
}

#endif //EXCEPTIONS_H
