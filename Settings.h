#ifndef Settings_h
#define Settings_h

#include <Arduino.h>
#include <EEPROM.h>

class Settings {
  public:
    Settings();
    void setup();
    void toogleEditMode();
    void up();
    void down();
    void save();
    boolean isInEditMode();
    uint8_t menuOption();
    boolean isInModeCc();
    uint8_t channel();
    int8_t octave();
    int8_t transpose();

  private:
    boolean _editMode = false;
    uint8_t _menuOption = 1;
    boolean _modeCc = true;
    uint8_t _channel = 16;
    int8_t _octave = 0;
};
#endif

