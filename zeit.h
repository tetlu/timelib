#ifndef ZEIT_H_INCLUDED
#define ZEIT_H_INCLUDED

// Datum-Struktur
struct Date
{
    int day;
    int month;
    int year;
};

// Methodensignaturen
int day_of_the_year(struct Date date);
struct Date input_date();
int is_leapyear(struct Date date);
int get_days_for_month(struct Date date);
int exists_date(struct Date date);
int day_of_the_week_num(struct Date date);
const char* day_of_the_week(struct Date date);
int calender_week(struct Date date);

#endif // ZEIT_H_INCLUDED
