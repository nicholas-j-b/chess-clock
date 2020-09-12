#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

const uint8_t SEG_TEST[] = {
    SEG_A | SEG_B
};
uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
TM1637Display display(CLK, DIO);

void setup() {
    Serial.begin(9600);
    Serial.println("starting up...");
    display.setBrightness(0x0f);
}

void loop() {
    Serial.println("loop...");
    turnOffAll();
    delay(500);
}

void turnOnAll() {
    display.setSegments(data);
}

void turnOffAll() {
    display.setSegments(blank);
}