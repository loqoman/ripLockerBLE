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
#include "messageLib.h"

#define DEVICE "peripheral"
// Peripheral uart service
BLEUart bleuart;
String myMessage; // TODO

char messageCharArray[100];

int messageCharArraySize = sizeof(messageCharArray);

Message testMsg(millis());

bool awake; // Keeping better track of what state the peripheral is in 
double timeToSleep;

void setup() {
    Serial.begin(115200);
    setupAdvertising();
}

void loop() {
    // We've just turned on from a power reset. 
    // We're either:
    //      - Had our power cut suddenly during mid-operatio
    //      - Are just starting our operation

    // We nede to advertise and get a connection, then stay awake until we're told to go to sleep 

}
