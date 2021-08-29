// Thought Exersize: Can you write the entire program with exslusivly callbacks

// Coding the peripheral to send a ping through modbus

#include <Arduino.h>
#include <bluefruit.h>

SoftwareTimer testTimer;
// 1ms = 0.001s
// 1000ms = 1.0s
void* whatever;


void testTimer_callback(TimerHandle_t xTimerID){

    // The freeRTOS timer id
    (void) xTimerID;

    digitalToggle(LED_RED);

    delay(1);
}

void setup() {
    //Bluefruit.begin();
    testTimer.begin(30000, testTimer_callback, whatever, true);

    testTimer.start();

    digitalToggle(PIN_LED2);
    delay(100);

    sd_power_mode_set(NRF_POWER_MODE_LOWPWR);

        // Do nothing :)
    __WFI();

    digitalToggle(PIN_LED2);
    delay(100);
    digitalToggle(PIN_LED2);
    delay(100);
    digitalToggle(PIN_LED2);
    delay(100);
    digitalToggle(PIN_LED2);
    delay(100);
}

void loop() {


}
