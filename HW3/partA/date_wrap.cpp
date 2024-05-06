#include <iostream>
#include <cassert>
#include "exceptions.h"
#include "date_wrap.h"

/*static functions declaration*/

/**
* dateIsValid: checks if a given date is a legal date
*
* @param day - Target day.
* @param month - Target month.
*
* @return
* 	false if the day or the month are not valid
* 	true if the date iis valid
*/

static bool isValidDate(int day, int month);

/*end of static functions declaration*/


/*static functions implementation*/

bool isValidDate(int day, int month)
{
	if (month < mtm::min_month || month > mtm::max_month)
	{
		return false;
	}

	if (day < mtm::min_day || day > mtm::max_day)
	{
		return false;
	}

	return true;
}

/* end of static functions implementation*/


mtm::DateWrap::DateWrap(int day, int month, int year)
{
	if (!isValidDate(day, month))
	{
		throw mtm::InvalidDate();
	}

	this->date_day = day;
	this->date_month = month;
	this->date_year = year;

}

int mtm::DateWrap::day() const
{
	return this->date_day;
}

int mtm::DateWrap::month() const
{
	return this->date_month;
}

int mtm::DateWrap::year() const
{
	return this->date_year;
}

mtm::DateWrap mtm::DateWrap::operator++(int)
{
    assert(isValidDate(this->date_day, this->date_month));
	DateWrap old_date(this->date_day, this->date_month, this->date_year);

	Date temp_date = dateCreate(this->date_day, this->date_month, this->date_year);
	if (temp_date == NULL)
	{
		throw std::bad_alloc();
	}

	dateTick(temp_date);

	assert(&this->date_day != NULL && &this->date_month != NULL && &this->date_year != NULL);
	dateGet(temp_date, &this->date_day, &this->date_month, &this->date_year);

	dateDestroy(temp_date);
	return old_date;

}

bool mtm::operator>(const DateWrap& date1, const DateWrap& date2)
{
	Date temp_date1 = dateCreate(date1.day(), date1.month(), date1.year());
	if (temp_date1 == NULL)
	{
		throw std::bad_alloc();
	}

	Date temp_date2 = dateCreate(date2.day(), date2.month(), date2.year());
	if (temp_date2 == NULL)
	{
		dateDestroy(temp_date1);
		throw std::bad_alloc();
	}

	int result = dateCompare(temp_date1, temp_date2);

	dateDestroy(temp_date1);
	dateDestroy(temp_date2);

	return result > 0;
}

bool mtm::operator==(const DateWrap& date1, const DateWrap& date2)
{
	Date temp_date1 = dateCreate(date1.day(), date1.month(), date1.year());
	if (temp_date1 == NULL)
	{
		throw std::bad_alloc();
	}

	Date temp_date2 = dateCreate(date2.day(), date2.month(), date2.year());
	if (temp_date2 == NULL)
	{
		dateDestroy(temp_date1);
		throw std::bad_alloc();
	}

	int result = dateCompare(temp_date1, temp_date2);

	dateDestroy(temp_date1);
	dateDestroy(temp_date2);

	return result == 0;
}

bool mtm::operator<(const DateWrap& date1, const DateWrap& date2)
{
		return date2 > date1;
}

bool mtm::operator<=(const DateWrap& date1, const DateWrap& date2)
{
		return !(date1 > date2);

}

bool mtm::operator>=(const DateWrap& date1, const DateWrap& date2)
{
		return !(date1 < date2);
}

bool mtm::operator!=(const DateWrap& date1, const DateWrap& date2)
{
		return !(date1 == date2);
}

mtm::DateWrap& mtm::operator+=(DateWrap& date, int days)
{
	if (days < 0)
	{
		throw mtm::NegativeDays();
	}

	for (int i = 0; i < days; i++)
	{
			date++;
	}

	return date;

}

mtm::DateWrap mtm::operator+(const DateWrap& date, int days)
{
	if (days < 0)
	{
		throw mtm::NegativeDays();
	}
	assert(isValidDate(date.day(), date.month()));
	DateWrap result(date);
    
    result += days;
	
	return result;
}

mtm::DateWrap mtm::operator+(int days, const DateWrap& date)
{
    return date + days;
}

std::ostream& mtm::operator<<(std::ostream& os, const DateWrap& date)
{
	return os << date.day() << "/" << date.month() << "/" << date.year();
}
