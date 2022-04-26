/**
* Programm zum herausfinden des numerischen Jahrestages
* eines eingegebenen Datums
* Autor: Lukas Tetzlaff
* Erstellt am 15.03.2022
*
*/

#include <stdio.h>
#include <stdlib.h>

int day_of_the_year(int day, int month, int year);
void input_date(int *day, int *month, int *year);
int is_leapyear(int year);
int get_days_for_month(int month, int year);
int exists_date(int day, int month, int year);

int main()
{
    // Varibalen deklarieren
    int day = 1;
    int year = 0;
    int month = 1;

    input_date(&day, &month, &year);

    // Ausgabe
    printf("Heute ist der %i. Tag des Jahres.", day_of_the_year(day, month, year));
    return 0;
}

int day_of_the_year(int day, int month, int year) {
    // Zusammenrechnen der Tage in allen Monaten bis zum angegebenen Monat
    for (int i = 1; i < month; i++) {
        if (get_days_for_month(i, year)) {
            day += get_days_for_month(i, year);
        } else {
            printf("Ungueltiger Monat oder Jahr: %i", i);
            printf(" , ", year);
        }
    }
    return day;
}

void input_date(int *day, int *month, int *year) {
    // Eingabeprompts mit Überprüfung der Validität der Eingaben
    printf("*** Tag des Jahres ***\n");
    do {
        printf("Geben sie das Jahr ein: ");
        scanf("%i", *&year);
        printf("Geben sie den Monat ein: ");
        scanf("%i", *&month);
        printf("Geben sie den Tag ein: ");
        scanf("%i", *&day);
    } while (! exists_date(*day, *month, *year));
}

// Funktion zum herausfinden, ob ein gegebenes Jahr ein Schaltjahr ist
int is_leapyear(int year) {
    if (year < 1582) return -1;
    short leapyear = 0;
    if ((year % 4) == 0) {
        if ((year % 100) == 0) {
            if ((year % 400) == 0) {
                leapyear = 1;
            } else leapyear = 0;
        } else leapyear = 1;
    } else leapyear = 0;

    if (leapyear) return 1;
    return 0;
}

int get_days_for_month(int month, int year) {
    if (month >= 1 && month <= 12) {
        int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // Wenn Schaltjahr, 29 Tage im Februar
        if(is_leapyear(year)) {
            month_days[2] = 29;
        } else {
            month_days[2] = 28;
        }
    return month_days[month];
    }
    return -1;
}

int exists_date(int day, int month, int year) {
    if (year > 2400 || year < 1582
        || day < 1 || day > get_days_for_month(month, year)
        || month < 1 || month > 12) {
        return 0;
    }
    return 1;
}

