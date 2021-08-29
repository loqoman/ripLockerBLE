// Personal/Programming/Projects/ripeLockerBLE
// Darwin Clark
//   for RipeLocker LLC

// This code is run on the Arduino and emulates a device (Such as a sensor) on the other end of the Half-Duplex MAX485
//  module. Because the system was not able to be tested with a physical sensor

// [ ] Accept a piece of data from Modbus, and re-transit that data with some form of acknowledgment 

#include <Arduino.h>

const int EnTxPin = 9; // Corresponds to pin D9 on (bootleg) Arduino nano
String readMessage;

void setup () {
    // TODO: Does baud rate matter here?
    Serial.begin(9600);

    // Setting up MAX module
    pinMode(EnTxPin, OUTPUT );
    digitalWrite(EnTxPin, LOW );
}

void loop (){
    // All we need to do is wait for a serial message and send some form of ping
    if (Serial.available() > 20){
        delay(100);
        readMessage = ((char) Serial.read()); 
        // In the itnerest of simplicity, I'm not acutally going to fully decode the message, just duplicate
        
        // Enable transmitting
        digitalWrite(EnTxPin, HIGH);
        Serial.print("Received the following message form the peripheral: ");
        Serial.println(readMessage);    // The "Time" element of the authentication acutally comes from the peripheral
 
        Serial.flush(); // Waits for the outgoing data to transmit
        digitalWrite(EnTxPin, LOW);
    }
    delay(10);
}
