#include "Pflanze.h"
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
Pflanze::Pflanze(String n, int fB, int bi, unsigned long lb, int bd)
    : name(n), feuchtigkeitsbedarf(fB), bewasserungsintervall(bi), letzteBewasserung(lb), bewasserungsdauer(bd) {}

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
