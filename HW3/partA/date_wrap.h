#ifndef DATE_WRAP_H_
#define DATE_WRAP_H_

#include <iostream>

extern "C"
{
#include "date.h"
}

namespace mtm
{
    //const variables
    const int min_day = 1;
    const int max_day = 30;
    const int min_month = 1;
    const int max_month = 12;

	/** class for defining a wrapper for C date */

	class DateWrap {
		int date_day;
		int date_month;
		int date_year;


	public:
		/*constructor*/
		DateWrap(int day, int month, int year); // DateWrap date1
		/*copy constructor*/
		DateWrap(const DateWrap& date) = default; // DateWrap date1(date2);
        /*assignment operator*/
        DateWrap& operator=(const DateWrap& date) = default; // date1=date2;
		/*destructor*/
		~DateWrap() = default;
		int day() const;
		int month() const;
		int year() const;
		DateWrap operator++(int);// Postfix, a dummy int
	};

	bool operator>(const DateWrap& date1, const DateWrap& date2);
	bool operator==(const DateWrap& date1, const DateWrap& date2); // d1==d2
	bool operator<(const DateWrap& date1, const DateWrap& date2); // d1<d2
	bool operator<=(const DateWrap& date1, const DateWrap& date2);
	bool operator>=(const DateWrap& date1, const DateWrap& date2);
	bool operator!=(const DateWrap& date1, const DateWrap& date2);
	DateWrap& operator+=(DateWrap& date, int days); // d1 += d2
	DateWrap operator+(const DateWrap& date, int days);
	DateWrap operator+(int days, const DateWrap& date);
	std::ostream& operator<<(std::ostream& os, const DateWrap& date); // cout << d1;
}
#endif // DATE_WRAP_H_
