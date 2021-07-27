
#include <Arduino.h>
#include <bluefruit.h>

#include "peripheralLib.h"
#include "messageLib.h"

extern BLEUart bleuart;

// ===== Callbacks ===== // 
void periphConnectCallback(uint16_t conn_handle) {
// Get the reference to current connection
    BLEConnection* connection = Bluefruit.Connection(conn_handle);

    char peer_name[32] = { 0 };
    connection->getPeerName(peer_name, sizeof(peer_name));

    Serial.print("[Prph] Connected to ");
    Serial.println(peer_name);
}

void periphDisconnectCallback(uint16_t conn_handle, uint8_t reason) {
    (void) conn_handle;
    (void) reason;

    Serial.println();
    Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

    // When we(peripheral) get a message
void UARTrxCallback(BLEClientUart& uart_svc) {
    Serial.print("[RX]: ");

    while (uart_svc.available() ) {
        Serial.print((char) uart_svc.read() );
    }


    Serial.println();
}

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
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}


