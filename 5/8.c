/* There is no error-checking in day_of_year or month_day. Remedy this defect. */
#include <stdio.h>
#include <assert.h>

/* Lowest allowed year: year Great Britain switched to the Gregorian calendar
 * for which the leap year validation is valid
 * */
#define LOWEST_ALLOWED_YEAR 1752

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
	int year, month, day, yearday;

	for (year = 1970; year <= 2000; ++year) {
		for (yearday = 1; yearday < 366; ++yearday) {
			assert(month_day(year, yearday, &month, &day) != -1);
			assert((day_of_year(year, month, day) == yearday));
		}
	}

	return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (year < 1752 || month < 1 || month > 12 || day < 1)
		return -1;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if (day > daytab[leap][month])
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	if (year < 1752 || yearday < 1)
		return -1;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if ((leap && yearday > 366) || (!leap && yearday > 365))
		return -1;

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;

	return 0;
}
