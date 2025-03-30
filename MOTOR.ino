#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

#define TOP_SENSOR A0  // Top soil sensor (tank full detection)
#define BOTTOM_SENSOR A1 // Bottom soil sensor (tank empty detection)
#define RELAY 7         // Relay controlling the motor

#define TOP_THRESHOLD 20   // Upper limit (water full)
#define BOTTOM_THRESHOLD 1 // Lower limit (water empty)

Adafruit_LiquidCrystal lcd(0); // Adafruit I2C LCD at address 0x27

void setup() {
    pinMode(RELAY, OUTPUT);
    digitalWrite(RELAY, LOW); // Initially keep motor OFF
    
    lcd.begin(16, 2);
    lcd.setBacklight(1);
    lcd.setCursor(0, 0);
    lcd.print("Water Tank Ctrl");
}

void loop() {
    int topSensorValue = analogRead(TOP_SENSOR) * 100 / 1023; // Convert to percentage
    int bottomSensorValue = analogRead(BOTTOM_SENSOR) * 100 / 1023;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Top: "); lcd.print(topSensorValue); lcd.print("% ");
    lcd.setCursor(0, 1);
    lcd.print("Bottom: "); lcd.print(bottomSensorValue); lcd.print("% ");

    if (topSensorValue >= TOP_THRESHOLD) {
        digitalWrite(RELAY, LOW); // Turn OFF motor
        lcd.setCursor(1, 1);
        lcd.print("OFF ");
    } 
    else if (bottomSensorValue <= BOTTOM_THRESHOLD) {
        digitalWrite(RELAY, HIGH); // Turn ON motor
        lcd.setCursor(1, 1);
        lcd.print("ON ");
    }
    
    delay(2000); // Wait 2 seconds before next check
}
