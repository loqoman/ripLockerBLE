
// NB. THIS IS CONNECTABLE FROM THE PHONE AND NEEDS TO BE DEBUGABBLE FROM THE PHONE

// --- Peripheral --- 
#include <Arduino.h>
#include <bluefruit.h>
#include "peripheralLib.h"

// Peripheral uart service
BLEUart bleuart;
String myMessage; // TODO

bool awake; 

void setup() {
  Serial.begin(115200);
  setupAdvertising(bleuart);
}

void loop() {
  // This loop was initally a 'forwarder': [HW Object (Sensor)] -> [BLE periph] -> [BLE Client]

  // Just send *something*
  // TODO: Do some incrementing later
  while (bleuart.available()) {
    delay(2000);
    const char* str = "Test From Periph";

    bleuart.write(str);
  }
}