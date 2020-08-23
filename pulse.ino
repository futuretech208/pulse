#include "MAX30100_PulseOximeter.h"
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.
#define refresh     1000

PulseOximeter pox;

uint32_t lastRefresh = 0;

void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  if (!pox.begin())
  {
    lcd.setCursor(0, 1);
    lcd.print("FAILED");
    // for (;;);
  } else
  {
    lcd.setCursor(0, 1);
    lcd.print("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  pox.update();

  if (millis() - lastRefresh > refresh)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BPM : ");
    lcd.print(pox.getHeartRate());
    lcd.setCursor(0, 1);
    lcd.print("SpO2: ");
    lcd.print(pox.getSpO2());
    lcd.print(" %");
    lastRefresh = millis();
  }
}
