#ifndef MidiKeyboard_h
#define MidiKeyboard_h

#include <Arduino.h>
#include <MIDI.h>
#include <Commons.h>
#include "Settings.h"

class MidiKeyboard {
  public:
    MidiKeyboard();
    void setup(Settings *settings, Led *led);
    void loop();
    
  private:
    Settings *_settings;
    Led *_led;
    void midiButton(uint8_t index);
    uint8_t getControlChangeValue(uint8_t index);
    uint8_t getNoteValue(uint8_t index);
    uint8_t assignFreePin();
    boolean contains(uint8_t value);
};
#endif
