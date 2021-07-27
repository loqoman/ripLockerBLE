// Personal/Programming/Projects/ripeLockerBLE
// Darwin Clark
//   for RipeLocker LLC

// GOAL: Have this file be less than 100 lines

// [X] Scan for the other BLE feather and see it 
// [X] Send a custom message between the feathers

// NB. THIS IS CONNECTABLE FROM THE PHONE AND NEEDS TO BE DEBUGABBLE FROM THE PHONE

// --- Peripheral --- 
#include <Arduino.h>
#include <bluefruit.h>
#include "peripheralLib.h"

#define DEVICE "peripheral"
// Peripheral uart service
BLEUart bleuart;
String myMessage; // TODO

bool awake; 

void setup() {
    Serial.begin(115200);
    setupAdvertising();
}

void loop() {
  	// This loop was initally a 'forwarder': [HW Object (Sensor)] -> [BLE periph] -> ||wall||  [BLE Client]

  	// Just send *something*
  	// TODO: Do some incrementing later
	while (true) {
		delay(2000);
		const char* str = "Test From Periph";
		bleuart.write(str);
		digitalToggle(PIN_LED2); // TODO: Time this seperate from connection status LED
	}
}
