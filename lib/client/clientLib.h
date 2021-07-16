#include <bluefruit.h>
#include "messageLib.h"
BLEClientUart clientUART;


// ===== Callbacks ===== // 
// I *could* fit the callbacks inside the client object
void scanCallback(ble_gap_evt_adv_report_t* report);    // When we scan and find something

void connectCallback(uint16_t conn_handle);     // When we make a new connection

void disconnectCallback(uint16_t conn_handle, uint8_t reason);  // When we disconnect

void UARTrxCallback(BLEClientUart& uart_svc);   // When we get a message


// ===== Helper Functiosn ======
void setupScanner(); // 
