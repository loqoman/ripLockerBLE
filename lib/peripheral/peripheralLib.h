#include <bluefruit.h>
#include "messageLib.h"
// ===== BLUETOOTH Callbacks ===== // 
void periphConnectCallback(uint16_t conn_handle);
void periphDisconnectCallback(uint16_t conn_handle, uint8_t reason);
void UARTrxCallback(BLEClientUart& uart_svc);   // When we(peripheral) get a message

// ===== MESSAGE Callbacks ===== //

// Likely will need access to global scope variables
// TODO: This feels like a place for metaprogramming, but I don't know enough C++ to properly implemnt
//        a template or something similar
void KEEPALIVECallback();
void REQRBATTCallback();
void REQREADCallback();
void REQROUNDTRIPCallback();
void GOTOSLEEPCallback();
void SETSLEEPTIMECallback();


// ===== Helper Functions ===== //

void setupAdvertising();
void handleMessage(String message);