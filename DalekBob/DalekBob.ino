
/*
 * NativeSdk by Simon Peter
 * Access functionality from the Espressif ESP8266 SDK
 * This example code is in the public domain
 * 
 * This is for advanced users.
 * Note that this makes your code dependent on the ESP8266, which is generally
 * a bad idea. So you should try to use esp8266/Arduino functionality
 * where possible instead, in order to abstract away the hardware dependency.
 */
//include <Packets.h>

// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
void setup() {
  Serial.begin(115200);
}
unsigned long ulLastMessageTime;
void loop() {
  unsigned long ulThisLoopTime = millis();
  // Call Espressif SDK functionality - wrapped in ifdef so that it still
  // compiles on other platforms
   if (Serial.available()) {
    ulLastMessageTime = millis();
    int inByte = Serial.read();
    Serial.write("Recieved byte ");
    Serial.write(inByte);
    Serial.write("\n\r");
  }
  if(ulLastMessageTime < ulThisLoopTime - ((unsigned long)5000))
  {
    ulLastMessageTime = millis();
    Serial.write("Recieve timeout");
    Serial.write("\n\r");
  }
  delay(10);
}
