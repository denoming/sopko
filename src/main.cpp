#include <Arduino.h>

#define LED_PIN 2

void
setup()
{
    /* Init serial */
    Serial.begin(9600);
    while (!Serial) {
        delay(10);
    }

    pinMode(LED_PIN, OUTPUT);
}

void
loop()
{
    digitalWrite(LED_PIN, HIGH);
    delay(1500);
    digitalWrite(LED_PIN, LOW);
}