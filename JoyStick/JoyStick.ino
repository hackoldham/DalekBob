/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/AnalogInput

 */

int sensorPinX = A0;
int sensorPinY = A1;
int sensorPinBtn = A2;
int sensorPinX2 = A3;
int sensorPinY2 = A4;
int sensorPinBtn2 = A5;
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  
}

void loop() {
  // read the value from the sensor:
  int iX = analogRead(sensorPinX);
  int iY = analogRead(sensorPinY);
  int iZ = analogRead(sensorPinBtn);
  int iX2 = analogRead(sensorPinX2);
  int iY2 = analogRead(sensorPinY2);
  int iZ2 = analogRead(sensorPinBtn2);
  
  Serial.print("X: ");
  Serial.print(iX);
  Serial.print(" Y: ");
  Serial.print(iY);
  Serial.print(" Btn: ");
  Serial.println(iZ);
  Serial.print("X2: ");
  Serial.print(iX2);
  Serial.print(" Y2: ");
  Serial.print(iY2);
  Serial.print(" Btn2: ");
  Serial.println(iZ2);
  delay(100);
}
