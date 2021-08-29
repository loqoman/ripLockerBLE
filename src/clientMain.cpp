// Personal/Programming/Projects/ripeLockerBLE
// Darwin Clark
//   for RipeLocker LLC

// GOAL: Have this file be less than 100 lines

// [X] Scan for the other BLE feather and see it 
// [X] Send a custom message between the feathers
// [ ] TODO: Allow bluetooth debugging through phone
// [ ] TODO: Write Serial Interface 
// --- Server --- 
#include <Arduino.h>
#include <bluefruit.h>
#include "clientLib.h"
#include "messageLib.h"

#define DEVICE "client"

BLEClientUart clientUart;

Message testMsg(millis());

String myMessage; // TODO
String loqoString;
char messageCharArray[100];
int messageCharArraySize = sizeof(messageCharArray);


void setup() {
	// Do nothing :)
	Serial.begin(115200);
	setupScanner();

	// --- messageLib testing --
	testMsg.type = Message::messageType::KEEPALIVE;
	testMsg.payload = 2;

	delay(5000);
	myMessage = testMsg.encodeToWire(millis());
	myMessage.toCharArray(messageCharArray, messageCharArraySize);
	clientUart.write(messageCharArray);
	// --- end of messageLib testing ---

}


void loop() {
	// Do nothing :)


	// Dump this at the bottom of each loop
	delay(1000);

	// Listening to the controller
	if(checkForSerial()) {
		loqoString = readSerial();
		Serial.print("[Client] Read the following from the serial port: ");
		Serial.println(loqoString);

		// Add code to do something with loqoString
	}

}

