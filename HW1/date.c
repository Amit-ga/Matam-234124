#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "date.h"

#define MIN_DAY 1
#define MAX_DAY 30
#define MIN_MONTH 1
#define MAX_MONTH 12
#define DATE_TWO_FIRST 2
#define DATE_ONE_FIRST -2
#define DATES_ARE_EQUAL 0
#define ERROR -1

struct Date_t
{
	int day;
	int month;
	int year;
};

/*static functions*/
/**
* dateIsValid: checks if a given date is a legal date
*
* @param day - day of the  month.
* @param month - month of the year.
* @return
* 	false if the day or the month are not valid
* 	true if the date iis valid
*/
static bool dateIsValid(int day, int month);

bool dateIsValid(int day, int month)
{
	if (month < MIN_MONTH || month > MAX_MONTH)
	{
		return false;
	}

	if (day < MIN_DAY || day > MAX_DAY)
	{
		return false;
	}

	return true;
}

/*end of static functions*/


Date dateCreate(int day, int month, int year)
{
	if (dateIsValid(day, month) == false)
	{

		return NULL;

	}

	Date date = malloc(sizeof(*date));
	if (date == NULL)
	{
		return NULL;
	}

	date->day = day;
	date->month = month;
	date->year = year;

	return date;
}

void dateDestroy(Date date)
{
	free(date);
}

Date dateCopy(Date date)
{
	if (date == NULL)
	{
		return NULL;
	}

	Date new_date = dateCreate(date->day, date->month, date->year);
	if (new_date == NULL)
	{
		return NULL;
	}

	return new_date;
}

bool dateGet(Date date, int* day, int* month, int* year)
{
	if (date == NULL || day == NULL || month == NULL || year == NULL)
	{
		return false;
	}

	*day = date->day;
	*month = date->month;
	*year = date->year;
	return true;
}

int dateCompare(Date date1, Date date2)
{
	if (date1 == NULL || date2 == NULL)
	{
		return 0;
	}

	if (date1->year < date2->year)
	{
		return DATE_ONE_FIRST;
	}

	else
	{
		if (date1->year > date2->year)
		{
			return DATE_TWO_FIRST;
		}

		else
		{
			assert(date1->year == date2->year);
			if (date1->month < date2->month)
			{
				return DATE_ONE_FIRST;
			}
			else
			{
				if (date1->month > date2->month)
				{
					return DATE_TWO_FIRST;
				}
				else
				{
					assert(date1->month == date2->month);
					{
						if (date1->day < date2->day)
						{
							return DATE_ONE_FIRST;
						}

						else
						{
							if (date1->day > date2->day)
							{
								return DATE_TWO_FIRST;
							}
							else
							{
								assert(date1->day == date2->day);
								return DATES_ARE_EQUAL;
							}
						}
					}
				}
			}
		}
	}

	return -1; // should not get here
}

void dateTick(Date date)
{
	if (date != NULL)
	{
		if (date->day < 30)
		{
			date->day = date->day + 1;
		}
		else
		{
			assert(date->day == 30);
			date->day = 1;

			if (date->month < 12)
			{
				date->month = date->month + 1;
			}

			else
			{
				assert(date->month == 12);
				date->month = 1;
				date->year = date->year + 1;
			}
		}
	}
}