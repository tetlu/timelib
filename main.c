/**
* Programm zum herausfinden des numerischen Jahrestages
* eines eingegebenen Datums
* Autor: Lukas Tetzlaff
* Erstellt am 15.03.2022
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "zeit.h"

int main() {
    // Variablen deklarieren
    int day = 1;
    int year = 0;
    int month = 1;

    // Eingabeprompt
    input_date(&day, &month, &year);

    // Ausgabe
    printf("Heute ist %s", day_of_the_week(day, month, year));
    printf(", der %i. Tag des Jahres", day_of_the_year(day, month, year));
    printf(" in der %i. Kalenderwoche", calender_week(day, month, year));
    return 0;
}
