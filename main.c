#include <stdio.h>
#include <stdlib.h>
#include "zeit.h"

/**
* Funktion zum berechnen eines Jahrtages anhand des gegebenen Datums
*
* @param int day
* @param int month
* @param int year
*
* @return int Nummer des Tages
*/
int day_of_the_year(int day, int month, int year) {
    // Zusammenrechnen der Tage in allen Monaten bis zum angegebenen Monat
    for (int i = 1; i < month; i++) {
        if (get_days_for_month(i, year)) {
            day += get_days_for_month(i, year);
        } else {
            printf("Ungueltiger Monat oder Jahr: %i", i);
            printf(" , %i", year);
        }
    }
    return day;
}

/**
* Funktion zum ausgeben eines Eingabepromptes und einlesen der Parameter
*
* @param *int day
* @param *int month
* @param *int year
*
*/
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

/**
* Funktion zum herausfinden, ob ein gegebenes Jahr ein Schaltjahr ist
*
* @param int year
*
* @return int 1 = Schaltjahr, 0 = kein Schaltjahr, -1 = ungültiges Jahr
*/
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

/**
* Funktion zum herausfinden der Anzahl Tage im gegebenen Jahrmonat
*
* @param int month
* @param int year
*
* @return int Anzahl von Tagen (1-31), wenn ein gültiger Monat eingegeben wurde,
              -1 wenn ein ungültiger Monat oder Jahr übergeben wurde
*/
int get_days_for_month(int month, int year) {
    if (month >= 1 && month <= 12 && year >= 1582) {
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

/**
* Funktion zum herausfinden, ob ein gegebenes Datum existiert/gültig ist
*
* @param int day
* @param int month
* @param int year
*
* @return int 1 = Datum gültig, 0 = Datum nicht gültig
*/
int exists_date(int day, int month, int year) {
    if (year > 2400 || year < 1582
        || day < 1 || day > get_days_for_month(month, year)
        || month < 1 || month > 12) {
        return 0;
    }
    return 1;
}

/**
* Funktion zum herausfinden des Wochentages eines gegebenen Datums
*
* @param int day
* @param int month
* @param int year
*
* @return int Nummer des Wochentages (1 = Montag, 7 = Sonntag)
*/
int day_of_the_week_num(int day, int month, int year) {
    // Benutzung der Zeller-Regel (https://www.rosettacode.org/wiki/Day_of_the_week#C)
    int adjustment, mm, yy;
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	return (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

/**
* Funktion zum herausfinden des Wochentages eines gegebenen Datums als String
*
* @param int day
* @param int month
* @param int year
*
* @return const char* String des ausgeschriebenen Wochentag
*/
const char* day_of_the_week(int day, int month, int year) {
    char *weekdays[7] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
	return weekdays[day_of_the_week_num(day, month, year)];
}

/**
* Funktion zum herausfinden der aktuellen Kalenderwoche
*
* @param int day
* @param int month
* @param int year
*
* @return int Nummer der Kalenderwoche
*/
int calender_week(int day, int month, int year) {
    // Quelle des Vorgehens: https://www.computerwoche.de/a/kalenderwoche-ermitteln,1099100#:~:text=(3)%20Ist%20der%20Wochentag%20aus,%22%20aus%20(3)%20addieren.
    int wochentag = day_of_the_week_num(1, 1, year);
    int jahrtag = day_of_the_year(day, month, year);
    int basisWoche = 1 - (wochentag > 4);
    int wochenAnzahl = jahrtag / 7 + basisWoche;
    wochentag += jahrtag % 7;
    if (wochentag > 7) {
        wochenAnzahl++;
    }
	return wochenAnzahl;
}
