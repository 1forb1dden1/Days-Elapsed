#include <iostream>
using namespace std;

const int Jan = 1;
const int Feb = 2;
const int Mar = 3;
const int Apr = 4;
const int May = 5;
const int Jun = 6;
const int Jul = 7;
const int Aug = 8;
const int Sep = 9;
const int Oct = 10;
const int Nov = 11;
const int Dec = 12;
const int Months = 12;

const string Month_Names[12] = { "January", "February", "March", "April", "May", "June", "July","August", "September", "October", "November", "December" };
long days_in_a_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 30, 30, 31 };

long compute_julian_day(long, long, long);
long query_for_valid_month();
long query_for_valid_day(long, long);
long return_day(long);
long return_month(long);
long return_year(long);
long return_days_in_month(long, long);
long return_days_in_year(long);
long return_julian_number(long, long, long);
void int_to_month(long);

bool is_a_leap_year(long year)
{
  bool return_value = false;
  if ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0))
  {
    return_value = true;
  }

  return return_value;
}

long return_days_in_month(long year_provided, long month_provided)
{
  long return_value = 0;

  days_in_a_month[Feb - 1] = ((is_a_leap_year(year_provided) == true ? return_value = 29 : return_value = 28));

  return_value = days_in_a_month[month_provided - 1];

  return return_value;
}

bool is_month_valid(long month_provided)
{
  bool return_value = false;

  if (month_provided <= 12 && month_provided >= 1)
  {
    return_value = true;
  }
  return return_value;
}

long return_days_in_year(long year_provided)
{
  return((is_a_leap_year(year_provided) == true) ? 366 : 365);
}

long return_julian_number(long year_provided, long month_provided, long day_provided)
{
  long julian_days = 0;

  for (int month = Jan; month < month_provided; month++)
    julian_days += return_days_in_month(year_provided, month);

  julian_days += day_provided;


  return julian_days;
}

long compute_julian_day(long year_provided, long month_provided, long day_provided)
{
  long total_days = 0;
  long leap_year = 0;
  long common_year = 0;
  long julian_day = return_julian_number(year_provided, month_provided, day_provided);

  while (year_provided > 1900)
  {
    if (is_a_leap_year(year_provided) == true)
    {
      year_provided--;
      leap_year++;
    }
    else
    {
      year_provided--;
      common_year++;
    }
  }

  total_days += (leap_year * 366);
  total_days += (common_year * 365);
  total_days += (julian_day)-1;


  return total_days;
}


void int_to_month(long month_provided)
{
  cout << Month_Names[month_provided - 1];
}

long query_for_valid_year(string prompt)
{
  long return_value = 0;
  cout << prompt;
  cin >> return_value;
  while (return_value < 1900)
  {
    cout << "The year is invalid. Try again: ";
    cin >> return_value;
  }
  return return_value;
}

long query_for_valid_month()
{
  long return_value = 0;

  cout << "Enter a valid month: ";
  cin >> return_value;
  while (is_month_valid(return_value) == false)
  {
    cout << "The value is invalid. Try again: ";
    cin >> return_value;
  }

  return return_value;
}

long query_for_valid_day(long year_provided, long month_provided)
{

  long return_value = 0;

  cout << "Enter a valid day: ";
  cin >> return_value;

  while (return_value > return_days_in_month(year_provided, month_provided) || return_value < 1)
  {
    cout << "The value is invalid. Try again: ";
    cin >> return_value;
  }

  return return_value;
}

long return_year(long julian_date)
{
  long year = 1900;
  long return_value = 0;

  while (julian_date >= return_days_in_year(year))
  {
    if (julian_date > is_a_leap_year(year))
    {
      year++;
      if (is_a_leap_year(year))
      {
        julian_date -= 366;
      }
      else
      {
        julian_date -= 365;
      }
    }
  }
  return year;
}

long return_month(long julian_date)
{
  long current_year = 0;
  long current_month = 1;
  long month = 0;

  if (is_a_leap_year(return_year(julian_date)))
  {
    days_in_a_month[1] = 29;
  }
  else
  {
    days_in_a_month[1] = 28;
  }

  while ((julian_date - return_days_in_year(return_year(julian_date)) >= 0))
  {
    julian_date -= return_days_in_year(return_year(julian_date));
  }
  while ((julian_date - days_in_a_month[month]) >= 0)
  {
    julian_date -= days_in_a_month[month];
    month++;
    current_month++;
  }

  return current_month;
}

long return_day(long julian_date)
{
  long current_year = 0;
  long current_month = 0;
  long month = 0;

  if (is_a_leap_year(return_year(julian_date)))
  {
    days_in_a_month[1] = 29;
  }
  else
  {
    days_in_a_month[1] = 28;
  }

  while ((julian_date - return_days_in_year(return_year(julian_date)) >= 0))
  {
    julian_date -= return_days_in_year(return_year(julian_date));
  }
  while ((julian_date - days_in_a_month[month]) >= 0)
  {
    julian_date -= days_in_a_month[month];
    month++;
  }

  return julian_date + 1;
}

int main()
{
  long year = 0; long month = 0; long day = 0; long julian_date = 0;
  year = query_for_valid_year("Enter a year >= 1900: "); month = query_for_valid_month(); day = query_for_valid_day(year, month);
  julian_date = compute_julian_day(year, month, day);
  cout << julian_date << " days have elapsed since 1 January 1900." << endl;
  return 0;
}
