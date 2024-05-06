#include "exceptions.h"

const char* mtm::InvalidDate::what() const noexcept
{
	return "Error: The input date is invalid";
}

const char* mtm::NegativeDays::what() const noexcept
{
	return "Error: A negativ days number was inserted";
}

const char* mtm::InvalidStudent::what() const noexcept
{
	return "Error: invaild student input \n A student is positive number between 1 and 1234567890";
}

const char* mtm::AlreadyRegistered::what() const noexcept
{
	return "Error: The student is already registered to this event";
}

const char* mtm::RegistrationBlocked::what() const noexcept
{
	return "Error: The student can not be registered to this event";
}

const char* mtm::NotRegistered::what() const noexcept
{
	return "Error: The student is not registered to this event";
}

const char* mtm::AlreadyInvited::what() const noexcept
{
	return "Error: The student has already been invited to this event ";
}

const char* mtm::NotSupported::what() const noexcept
{
	return "Error: this event type is not supported";
}

const char* mtm::DateMismatch::what() const noexcept
{
	return "Error: This event does not occure in the date of the festival!";
}

const char* mtm::InvalidNumber::what() const noexcept
{
	return "Error: number of event occurrences must be greater than 0 ";
}

const char* mtm::InvalidInterval::what() const noexcept
{
	return "Error: days interval must be greater than 0 ";
}

const char* mtm::EventAlreadyExists::what() const noexcept
{
	return "Error: one of the events already exists in the schedule ";
}

const char* mtm::EventDoesNotExist::what() const noexcept
{
	return "Error: This event does not exist in the schedule ";
}