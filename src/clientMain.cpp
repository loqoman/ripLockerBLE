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
	Serial.begin(115200);
	setupScanner();
}



void loop() {
	// Do nothing :)
}

