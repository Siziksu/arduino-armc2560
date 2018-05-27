#ifndef Screen_h
#define Screen_h

#include <Arduino.h>
#include "Settings.h"

class Screen {
  public:
    Screen();
    void setup();
    void clearScreen();
    void showLogo();
    void showMode(Settings settings);
    void showSettingsSaved(Settings settings);
    
  private:
    void showCcMode(uint8_t channel);
    void showNoteMode(int8_t octave);
    void showSettingsSaved();
};
#endif

