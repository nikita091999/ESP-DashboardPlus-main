#include "smoke.h"

// Variables
int gasValue = 0;
int threshold = 300;
int smokeCount = 0;
bool smokeDetected = false;

// 👉 Add LED pin (D0)
#define LED_PIN D0

void smokeSetup(LiquidCrystal &lcd) {
    pinMode(SMOKE_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);   // ✅ LED pin setup

    digitalWrite(LED_PIN, LOW); // LED OFF initially

    lcd.begin(16, 2);
    lcd.print("Smoke System");
    delay(2000);
    lcd.clear();
}

void smokeLoop(LiquidCrystal &lcd) {

    gasValue = analogRead(SMOKE_PIN);

    // 📟 SERIAL PRINT (Gas Value)
    Serial.print("Gas Value: ");
    Serial.println(gasValue);

    lcd.setCursor(0, 0);
    lcd.print("Gas:");
    lcd.print(gasValue);
    lcd.print("   ");

    static bool lastState = false;

    if (gasValue > threshold) {
        smokeDetected = true;

        if (!lastState) {
            smokeCount++;   // count once
        }
        lastState = true;

        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);   // 🔴 LED ON

        lcd.setCursor(0, 1);
        lcd.print("Cnt:");
        lcd.print(smokeCount);
        lcd.print(" SMOKE   ");

        // 🔥 SERIAL PRINT
        Serial.print("🔥 SMOKE DETECTED! Count: ");
        Serial.println(smokeCount);

    } else {
        smokeDetected = false;
        lastState = false;

        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);   // ⚫ LED OFF

        lcd.setCursor(0, 1);
        lcd.print("SAFE          ");

        // ✅ SERIAL PRINT
        Serial.println("✅ SAFE");
    }
}

// Getters
int getGasValue() {
    return gasValue;
}

int getSmokeCount() {
    return smokeCount;
}

bool isSmokeDetected() {
    return smokeDetected;
}
