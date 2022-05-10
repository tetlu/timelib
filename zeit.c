#include <stdio.h>
#include <stdlib.h>
#include "zeit.h"

/**
* Funktion zum berechnen eines Jahrtages anhand des gegebenen Datums
*
* @param struct Date date
*
* @return int Nummer des Tages
*/
int day_of_the_year(struct Date date) {
    // Zusammenrechnen der Tage in allen Monaten bis zum angegebenen Monat
    for (int i = 1; i < date.month; i++) {
        if (get_days_for_month(date)) {
            date.day += get_days_for_month(date);
        } else {
            printf("Ungueltiger Monat oder Jahr: %i", i);
            printf(" , %i", date.year);
        }
    }
    return date.day;
}

/**
* Funktion zum ausgeben eines Eingabepromptes und einlesen eines Datums
*
* @return struct Date date
*/
struct Date input_date() {
    struct Date date;
    // Eingabeprompts mit �berpr�fung der Validit�t der Eingaben
    printf("*** Tag des Jahres ***\n");
    do {
        printf("Geben sie das Jahr ein: ");
        scanf("%i", &date.year);
        printf("Geben sie den Monat ein: ");
        scanf("%i", &date.month);
        printf("Geben sie den Tag ein: ");
        scanf("%i", &date.day);
    } while (! exists_date(date));
    return date;

/**
* Funktion zum herausfinden, ob ein gegebenes Jahr ein Schaltjahr ist
*
* struct Date date | .year wird gebraucht
*
* @return int 1 = Schaltjahr, 0 = kein Schaltjahr, -1 = ungültiges Jahr
*/
int is_leapyear(struct Date date) {
    if (date.year < 1582) return -1;
    short leapyear = 0;
    if ((date.year % 4) == 0) {
        if ((date.year % 100) == 0) {
            if ((date.year % 400) == 0) {
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
* @param struct Date date | .month und .year werden gebraucht
*
* @return int Anzahl von Tagen (1-31), wenn ein gültiger Monat eingegeben wurde,
              -1 wenn ein ungültiger Monat oder Jahr übergeben wurde
*/
int get_days_for_month(struct Date date) {
    if (date.month >= 1 && date.month <= 12 && date.year >= 1582) {
        int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // Wenn Schaltjahr, 29 Tage im Februar
        if(is_leapyear(date)) {
            month_days[2] = 29;
        } else {
            month_days[2] = 28;
        }
        return month_days[date.month];
    }
    return -1;
}

/**
* Funktion zum herausfinden, ob ein gegebenes Datum existiert/gültig ist
*
* @param struct Date date
*
* @return int 1 = Datum gültig, 0 = Datum nicht gültig
*/
int exists_date(struct Date date) {
    if (date.year > 2400 || date.year < 1582
        || date.day < 1 || date.day > get_days_for_month(date)
        || date.month < 1 || date.month > 12) {
        return 0;
    }
    return 1;
}

/**
* Funktion zum herausfinden des Wochentages eines gegebenen Datums
*
* @param struct Date date
*
* @return int Nummer des Wochentages (1 = Montag, 7 = Sonntag)
*/
int day_of_the_week_num(struct Date date) {
    // Benutzung der Zeller-Regel (https://www.rosettacode.org/wiki/Day_of_the_week#C)
    int adjustment, mm, yy;
	adjustment = (14 - date.month) / 12;
	mm = date.month + 12 * adjustment - 2;
	yy = date.year - adjustment;
	return (date.day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

/**
* Funktion zum herausfinden des Wochentages eines gegebenen Datums als String
*
* @param struct Date date
*
* @return const char* String des ausgeschriebenen Wochentag
*/
const char* day_of_the_week(struct Date date) {
    char *weekdays[7] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
	return weekdays[day_of_the_week_num(date)];
}

/**
* Funktion zum herausfinden der aktuellen Kalenderwoche
*
* @param struct Date date
*
* @return int Nummer der Kalenderwoche
*/
int calender_week(struct Date date) {
    // Quelle des Vorgehens: https://www.computerwoche.de/a/kalenderwoche-ermitteln,1099100#:~:text=(3)%20Ist%20der%20Wochentag%20aus,%22%20aus%20(3)%20addieren.
    struct Date dateFirstDay;
    dateFirstDay.day = 1;
    dateFirstDay.month = 1;
    dateFirstDay.year = date.year;
    int wochentag = day_of_the_week_num(dateFirstDay);
    int jahrtag = day_of_the_year(date);
    int basisWoche = 1 - (wochentag > 4);
    int wochenAnzahl = jahrtag / 7 + basisWoche;
    wochentag += jahrtag % 7;
    if (wochentag > 7) {
        wochenAnzahl++;
    }
	return wochenAnzahl;
}
