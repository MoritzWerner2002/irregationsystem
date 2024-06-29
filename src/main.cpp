#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#define PUMP_PIN 18

RTC_DS3231 rtc;

int moist;

void pumpOn();
void pumpOff();

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
  // turn the LED on (HIGH is the voltage level)
  moist = analogRead(A0);
  Serial.print(">Moisture:");
  Serial.println(moist);

  /*if (moist > 650){
    pumpOn();
    delay(5000);
    pumpOff();
    }*/
   
  DateTime now = rtc.now();

  Serial.print("Datum: ");
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
  Serial.println();

  delay(100);
}

void pumpOn() {
    digitalWrite(PUMP_PIN, HIGH);
}

void pumpOff() {
    digitalWrite(PUMP_PIN, LOW);
}