#include <bluefruit.h>

// ===== Callbacks ===== // 
void periphConnectCallback(uint16_t conn_handle);

void periphDisconnectCallback(uint16_t conn_handle, uint8_t reason);

void UARTrxCallback(BLEClientUart& uart_svc);   // When we(peripheral) get a message

// ===== Helper Functions ===== //

void setupAdvertising(BLEUart inputUARTService);
