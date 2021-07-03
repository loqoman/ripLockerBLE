#include <bluefruit.h>

BLEClientUart clientUART;

void scanCallback(ble_gap_evt_adv_report_t* report);

void connectCallback(uint16_t conn_handle);

void disconnectCallback(uint16_t conn_handle, uint8_t reason);

void UARTrxCallback(BLEClientUart& uart_svc);

void initScanner();
