/**
* Programm zum herausfinden des numerischen Jahrestages
* eines eingegebenen Datums
* Autor: Lukas Tetzlaff
* Erstellt am 15.03.2022
*
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Varibalen deklarieren
    int monatsTage[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int jahr = 0;
    int monat = 1;
    int tag = 1;

    // Eingabeprompts mit Überprüfung der Validität der Eingaben
    printf("*** Tag des Jahres ***\n");
    do {
        printf("Geben sie das Jahr ein: ");
        scanf("%i", &jahr);
        // Wenn Schaltjahr, 29 Tage im Februar
        if(istSchaltjahr(jahr)) {
            monatsTage[2] = 29;
        }
    } while (jahr < 0);
    do {
        printf("Geben sie den Monat ein: ");
        scanf("%i", &monat);
    } while (monat <= 0 || monat > 12);
    do {
        printf("Geben sie den Tag ein: ");
        scanf("%i", &tag);
    } while (tag <= 0 || tag > monatsTage[monat]);

    // Zusammenrechnen der Tage in allen Monaten bis zum angegebenen
    for (int i = 0; i < monat; i++) {
        tag += monatsTage[i];
    }

    // Ausgabe
    printf("Heute ist der %i. Tag des Jahres.", tag);
    return 0;
}

// Funktion zum herausfinden, ob ein gegebenes Jahr ein Schaltjahr ist
int istSchaltjahr(int jahr) {
    short schaltjahr = 0;
    if ((jahr % 4) == 0) {
        if ((jahr % 100) == 0) {
            if ((jahr % 400) == 0) {
                schaltjahr = 1;
            } else schaltjahr = 0;
        } else schaltjahr = 1;
    } else schaltjahr = 0;

    if (schaltjahr) return 1;
    else return 0;
}
