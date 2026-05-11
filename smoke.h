#ifndef SMOKE_H
#define SMOKE_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define SMOKE_PIN A0
#define BUZZER_PIN D4

extern int gasValue;
extern int threshold;
extern int smokeCount;
extern bool smokeDetected;

void smokeSetup(LiquidCrystal &lcd);
void smokeLoop(LiquidCrystal &lcd);

// ✅ MUST BE PRESENT
int getGasValue();
int getSmokeCount();
bool isSmokeDetected();

#endif
