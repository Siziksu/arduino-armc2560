#ifndef Screen_h
#define Screen_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Settings.h"

class Screen {
  public:
    Screen();
    void setup(Settings *settings);
    void clearScreen();
    void showLogo();
    void drawMenu();
    void updateMenu();
    void showSettingsSaved();
    
  private:
    Settings *_settings;
};
#endif

