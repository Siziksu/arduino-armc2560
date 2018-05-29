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
    void showMode();
    void showSettingsSaved();
    
  private:
    Settings *_settings;
    void showCcMode(uint8_t channel);
    void showNoteMode(int8_t octave);
    void showMessage(String line1, int8_t size1, String line2, int8_t size2);
};
#endif
