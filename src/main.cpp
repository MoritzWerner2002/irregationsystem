#include <Arduino.h>

#define PUMP_PIN 18

int moist;

void pumpOn();
void pumpOff();

void setup()
{
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW); // Initialize the pump as off
  Serial.begin(9600);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  moist = analogRead(A0);
  Serial.print(">Moisture:");
  Serial.println(moist);

  if (moist > 650){
    pumpOn();
    delay(5000);
    pumpOff();
    }
   


  delay(100);
}

void pumpOn() {
    digitalWrite(PUMP_PIN, HIGH);
}

void pumpOff() {
    digitalWrite(PUMP_PIN, LOW);
}