#include "Pflanze.h"
#include <cmath>
#define PUMP_PIN 15

using namespace std;

void pumpOn() {
    digitalWrite(PUMP_PIN, HIGH);
    Serial.println("Pumpe eingeschaltet");
}

void pumpOff() {
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("Pumpe ausgeschaltet");
}


// Konstruktor-Definition
Pflanze::Pflanze(String n, int fB, int bi, unsigned long lb)
    : name(n), feuchtigkeitsbedarf(fB), bewasserungsintervall(bi), letzteBewasserung(lb) {}

//berechnung der Bewässerungsdauer aus schlauchlänge, wassermenge die die pflanze braucht und fördermenge der pumpe
int Pflanze::calcBewasserungsdauer(double Wassermenge, double schlauchlaenge) {

    double foerdergeschwindigkeit = 0.000035; //m^3/s
    double schlauchradius = 0.0035; //m
    double wasservol = M_PI * (pow(schlauchradius,2)) * schlauchlaenge + Wassermenge * 0.001;
    bewasserungsdauer = ceil((wasservol/foerdergeschwindigkeit) * 1000);
    return bewasserungsdauer; 
}

// Methode zur Messung der Feuchtigkeit
int Pflanze::feuchtigkeitMessen(int Pin) {
    return analogRead(Pin); 
}

// Methode zur Bewässerung
void Pflanze::bewasserungAusloesen() {
    pumpOn();
    Serial.print(name);
    Serial.println(" wird bewässert.");
    delay(bewasserungsdauer);
    pumpOff();
}
