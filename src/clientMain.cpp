// Personal/Programming/Projects/ripeLockerBLE
// Darwin Clark
//   for RipeLocker LLC

// GOAL: Have this file be less than 100 lines

// [X] Scan for the other BLE feather and see it 
// [X] Send a custom message between the feathers
// --- Server --- 
#include <Arduino.h>
#include <bluefruit.h>
#include "clientLib.h"

#define DEVICE "client"

BLEClientUart clientUart;

void setup() {
  // Do nothing :)
  setupScanner(clientUart);
}



void loop() {
  if (Bluefruit.Central.connected() ) {
    // Not discovered yet
    if (clientUart.discovered() ) {
      // Discovered means in working state
      // Get Serial input and send to Peripheral
      if (Serial.available() ) {
        delay(2); // delay a bit for all characters to arrive
        
        char str[20+1] = { 100 };
        // Serial.readBytes(str, 20);
        
        clientUart.print(str);
      }
    }
  }
}

