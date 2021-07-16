// Thought Exersize: Can you write the entire program with exslusivly callbacks

#include <Arduino.h>

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

    testTimer.begin(30000, testTimer_callback, whatever, true);

    testTimer.start();

    digitalToggle(PIN_LED2);
    delay(100);

    waitForEvent(); // Would be at the end of the program
}

void loop() {
    // Do nothing :)

}
