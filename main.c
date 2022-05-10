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
    struct Date datum;

    // Eingabeprompt
    datum = input_date();

    // Ausgabe
    printf("Heute ist %s", day_of_the_week(datum));
    printf(", der %i. Tag des Jahres", day_of_the_year(datum));
    printf(" in der %i. Kalenderwoche", calender_week(datum));
    return 0;
}
