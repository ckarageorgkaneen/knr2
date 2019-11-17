/* Rewrite the routines day_of_year and month_day with pointers instead of indexing. */
#include <stdio.h>
#include <assert.h>

/* Lowest allowed year: year Great Britain switched to the Gregorian calendar for which the leap year validation is valid */
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
	char *p;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	for (i = 1, p = &daytab[leap][1]; i < month; i++)
		day += *p++;
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	char *p;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	for (i = 1, p = &daytab[leap][1]; yearday > daytab[leap][i]; i++)
		yearday -= *p++;
	*pmonth = i;
	*pday = yearday;

	return 0;
}
