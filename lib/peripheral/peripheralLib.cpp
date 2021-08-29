
#include <Arduino.h>
#include <bluefruit.h>

#include "peripheralLib.h"
#include "messageLib.h"

extern BLEUart bleuart;
extern bool awake;
extern double timeToSleep; 

// ===== BLUETOOTH Callbacks ===== // 
void periphConnectCallback(uint16_t conn_handle) {
// Get the reference to current connection
    BLEConnection* connection = Bluefruit.Connection(conn_handle);

    char peer_name[32] = { 0 };
    connection->getPeerName(peer_name, sizeof(peer_name));

    Serial.print("[Periph] Connected to ");
    Serial.println(peer_name);
}

void periphDisconnectCallback(uint16_t conn_handle, uint8_t reason) {
    (void) conn_handle;
    (void) reason;

    Serial.println();
    Serial.print("[Periph] Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

    // When we(peripheral) get a message
void UARTrxCallback(BLEClientUart& uart_svc) {
    // Serial.print("[Client][Debug]: Available: ");
    // Serial.println(String(uart_svc.available()));
    
	Serial.print("[Peripheral][RX]: ");
    // TODO: Revisit this number as messages grow in size. This is very very bad because this will lead us to only partially read messages
    // IDEA: add brackets to either end of the message to veryify the start and end, then implement code that waits until the next read
	if (uart_svc.available() < 65) {
        return;
    }
    String readMessage;
	while (uart_svc.available()) {
        readMessage = ((char) uart_svc.read()); 
		Serial.print(readMessage);
	}

	Serial.println();    
}

// ===== MESSAGE Callbacks ====== //


// ====== Helper Function ====== // 
void setupAdvertising() {
    Bluefruit.autoConnLed(true);
    Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

    Bluefruit.begin();
    Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values

    // Configure and Start BLE Uart Service

    Bluefruit.setName("Bluefruit Perpherial (In-Container)");



    // Advertising packet

    Bluefruit.Periph.setConnectCallback(periphConnectCallback);
    Bluefruit.Periph.setDisconnectCallback(periphDisconnectCallback);

    bleuart.begin();

    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();



    // Include bleuart 128-bit uuid
    Bluefruit.Advertising.addService(bleuart);

    Bluefruit.ScanResponse.addName();

    /* Start Advertising
    * - Enable auto advertising if disconnected
    * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
    * - Timeout for fast mode is 30 seconds
    * - Start(timeout) with timeout = 0 will advertise forever (until connected)
    *
    * For recommended advertising interval
    * https://developer.apple.com/library/content/qa/qa1931/_index.html
    */
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);         // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);           // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                     // 0 = Don't stop advertising after n seconds
}

void handleMessage(String message) {
    // Figur eout what message it is
    Message inputMessage = Message::decodeFromWire(message);

    switch (inputMessage.type) {
        case Message::messageType::REQBATT:
            REQRBATTCallback();
        case Message::messageType::KEEPALIVE:
            KEEPALIVECallback();
            break;
        case Message::messageType::REQREAD:
            REQREADCallback();
            break;
        case Message::messageType::REQRUONDTRIP:
            REQROUNDTRIPCallback();
            break;
        case Message::messageType::GOTOSLEEP:
            GOTOSLEEPCallback();
            break;
        case Message::messageType::SETSLEEPTIME:
            SETSLEEPTIMECallback();
            break;

            
    }

}

void KEEPALIVECallback() {

    
}