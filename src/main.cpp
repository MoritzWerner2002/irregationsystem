#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include "pflanze.h"
#include <SPI.h>
#include <vector>

using namespace std;

#define PUMP_PIN 15
#define MOISTURE_SENSOR_PIN A0
#define MOISTURE_THRESHOLD 650 // Schwellenwert für Feuchtigkeit
#define PUMP_DURATION 5000 // Pumpe läuft 5 Sekunden

RTC_DS3231 rtc;
Pflanze aloeVera("Aloe Vera", MOISTURE_THRESHOLD, 10000, 0, PUMP_DURATION);

bool isSoilDry;
bool isDaytime;
int moist;
double mean_moist;

void setup()
{
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW); // Initialize the pump as off
    Wire.begin();
    rtc.begin();

    // Prüfen, ob die RTC läuft
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    Serial.begin(9600);
}

void loop()
{
  //for Schleife: 60s lang jede sekunde Feuchtigkeit Messen und dann mittels für mehr Sicherheit gegen Ausreiser
  int moist = 0;
  for (int i = 0; i < 60; i++) {
      moist += aloeVera.feuchtigkeitMessen(MOISTURE_SENSOR_PIN);  // Feuchtigkeitssensor lesen und Feuchtigkeit drauf addieren
      delay(1000);
  }
  double mean_moist = moist / 60.0;
  Serial.print(">Moisture: ");
  Serial.println(mean_moist);

  // Aktuelle Zeit abfragen
  DateTime now = rtc.now();

  // Bedingung 1: Feuchtigkeit ist unter dem Schwellenwert
  isSoilDry = moist > MOISTURE_THRESHOLD;

  // Bedingung 2: Es ist zwischen 6 Uhr morgens und 8 Uhr abends
  isDaytime = (now.hour() >= 8 && now.hour() <= 23);
  sleep_ms(60000);
  // Wenn beide Bedingungen erfüllt sind, die Pumpe einschalten
  if (isSoilDry && isDaytime) {
      aloeVera.bewasserungAusloesen();
    }

  // Datum und Uhrzeit ausgeben
  /*Serial.print("Datum: ");
  Serial.print(now.day());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.year());
  Serial.print(" - Zeit: ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();*/

  delay(1000); // 1 Sekunde warten
}