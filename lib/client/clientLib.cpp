// Callsbacks and Helper functions
#include <bluefruit.h>
#include "clientLib.h"
#include <Arduino.h>


// N.B This is needed to tell the compiler that clientUart is defined somewhere *else*, and to treat all references
//  to clientUart in this file are acoutally defined somewhere else

// In general, it's a bad idea to simply toss 'extern' in front of objects that you need access to (I.E what we did here)
//    This is because it's not immediately obvious fromt he function call (setupScanner/scanCallback) that they even NEED or operate on the
//    clientUart object, whereas if we passed it to the function, it's clear that some operation occurs with the input 
extern BLEClientUart clientUart;
// ===== Helper Functions ===== //

// TODO: Fix the lack of passing and the extern 
void setupScanner() {

    delay(10);   // for nrf52840 with native usb

    Serial.println("Bluefruit52 Central BLEUART Example");
    Serial.println("-----------------------------------\n");

    // Initialize Bluefruit with maximum connections as Peripheral = 0, Central = 1
    // SRAM usage required by SoftDevice will increase dramatically with number of connections
    Bluefruit.begin(0, 1);

    Bluefruit.setName("Bluefruit52 Central");

    // Init BLE Central Uart Serivce
    clientUart.begin();
    clientUart.setRxCallback(UARTrxCallback);

    // Increase Blink rate to different from PrPh advertising mode
    Bluefruit.setConnLedInterval(250);

    // Callbacks for Central
    Bluefruit.Central.setConnectCallback(connectCallback);
    Bluefruit.Central.setDisconnectCallback(disconnectCallback);

    /* Start Central Scanning
    * - Enable auto scan if disconnected
    * - Interval = 100 ms, window = 80 ms
    * - Don't use active scan
    * - Start(timeout) with timeout = 0 will scan forever (until connected)
    */
    Bluefruit.Scanner.setRxCallback(scanCallback);
    Bluefruit.Scanner.restartOnDisconnect(true);
    Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
    Bluefruit.Scanner.useActiveScan(false);
    Bluefruit.Scanner.start(0);                   // // 0 = Don't stop scanning after n seconds
}

// ====== Callbacks ====== //>
/**
 * Callback invoked when scanner pick up an advertising data
 * @param report Structural advertising data
 */
void scanCallback(ble_gap_evt_adv_report_t* report) {
      // Check if advertising contain BleUart service
    if (Bluefruit.Scanner.checkReportForService(report, clientUart) ) {
        Serial.println("BLE UART service detected. Connecting ... ");

        // Connect to device with bleuart service in advertising
        Bluefruit.Central.connect(report);
    } else {      
        // For Softdevice v6: after received a report, scanner will be paused
        // We need to call Scanner resume() to continue scanning
        Bluefruit.Scanner.resume();
    }
}

/**
 * Callback invoked when an connection is established
 * but AFTER we have scanned
 * @param conn_handle
 */
void connectCallback(uint16_t conn_handle) {     // When we make a new connection
    // TODO: Revisit the usefullness of the print statements
    Serial.println("[Client] Connected");
    Serial.println("[Client] Discovering BLE Uart Service ... ");

    // Need a BLEClientUART object here
    if (clientUart.discover(conn_handle) ) {
        Serial.println("[Client] Found BLE Uart Service. ");

        Serial.println("[Client] Enable TXD's notify");
        clientUart.enableTXD();

        Serial.println("[Client] Ready to receive from peripheral");
    } else {
        Serial.println("[Client] Found NONE");

        // disconnect since we couldn't find bleuart service
        Bluefruit.disconnect(conn_handle);
    }  
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */

void disconnectCallback(uint16_t conn_handle, uint8_t reason) {
	(void) conn_handle;
	(void) reason;
	
	Serial.print("[Client] Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

/**
 * Callback invoked when uart received data
 * @param uart_svc Reference object to the service where the data 
 * arrived. 
 */
void UARTrxCallback(BLEClientUart& uart_svc) {   // When we get a message

	Serial.print("[Client][RX]: ");
	
	while (uart_svc.available() ) {
		Serial.print((char) uart_svc.read());
	}

	Serial.println();
}

