#ifndef Settings_h
#define Settings_h

#include <Arduino.h>

class Settings {
  public:
    Settings();
    void setup();
    boolean isModeCc();
    uint8_t channel();
    int8_t octave();
    int8_t transpose();
    void toogleMode();
    void up();
    void down();
    void save();

  private:
    boolean _isModeCc = true;
    uint8_t _channel = 16;
    int8_t _octave = 0;
};
#endif

