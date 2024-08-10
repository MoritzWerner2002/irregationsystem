#ifndef PFLANZE_H
#define PFLANZE_H

#include <Arduino.h> // Falls du in der Arduino-Umgebung arbeitest

using namespace std;

class Pflanze {
private:
    String name;
    int feuchtigkeitsbedarf;
    int bewasserungsintervall;
    unsigned long letzteBewasserung;
    int bewasserungsdauer; //bedingt durch topfgröße, wasserbedarf und höhe über dem Behälter (Schlauch muss erst gefüllt werden)

public:
    // Konstruktor
    Pflanze(String n, int fb, int bi, unsigned long lb, int bd);

    // Methode zur Messung der Feuchtigkeit
    int feuchtigkeitMessen(int Pin);

    // Methode zur Bewässerung
    void bewasserungAusloesen();
};

#endif // PFLANZE_H