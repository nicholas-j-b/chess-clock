#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

uint8_t data[] = {0, 0, 0, 0};
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
unsigned long loopStartTime;
unsigned long gameStartTime;
unsigned long endTime;
unsigned long delayTime;
unsigned long gameTime = 25000;
unsigned long timeIncrement = 1000;

TM1637Display display(CLK, DIO);

void setup() {
    turnOffAll();
    Serial.begin(9600);
    Serial.println("starting up...");
    display.setBrightness(0x0f);
    beginGame(gameTime);
}

void loop() {
    initLoop();

    millisToDisplay(loopStartTime - gameStartTime);
    displayData();
    
    endLoop();
}

void initLoop() {
    loopStartTime = millis();
    Serial.println("loop...");
}

void endLoop() {
    for (size_t i = 0; i < 4; i++) {
        Serial.println(data[i]);
    }
    delayTime = millis() - loopStartTime + timeIncrement;
    delay(delayTime);
}

void beginGame(unsigned long length) {
    gameStartTime = millis();
    endTime = gameStartTime + length;
}

void displayData() {
    display.setSegments(data);
}

void turnOffAll() {
    display.setSegments(blank);
}

void millisToDisplay(unsigned long elapsedTime) {
    unsigned long remainingTime = (gameTime - elapsedTime) / 1000;
    uint8_t dig2 = remainingTime / 10;
    uint8_t dig3 = remainingTime - (dig2 * 10);
    Serial.print("dig2: ");
    Serial.println(dig2);
    Serial.print("dig3: ");
    Serial.println(dig3);
    data[2] = display.encodeDigit(dig2);
    data[3] = display.encodeDigit(dig3);
}
