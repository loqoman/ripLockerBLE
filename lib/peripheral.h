#include <bluefruit.h>

BLEUart bleuart;

String myMessage; // TODO

void periphConnectCallback(uint16_t conn_handle);

void periphDisconnectCallback(uint16_t conn_handle, uint8_t reason);

void setupAdvertising();

// TODO Need to write message function