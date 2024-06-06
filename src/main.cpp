/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
int moist;
void setup()
{
  // initialize LED digital pin as an output.

  Serial.begin(9600);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  moist = analogRead(A0);
  Serial.print(">Moisture:");
  Serial.println(moist);



  delay(100);
}
