#ifndef MidiController_h
#define MidiController_h

#include <Arduino.h>
#include <MIDI.h>
#include <Commons.h>
#include "Settings.h"

class MidiController {
  public:
    MidiController();
    void setup(Settings *settings, Led *led);
    void loop();
    void command(byte* command);
    
  private:
    Settings *_settings;
    Led *_led;
    void midiButton(uint8_t index);
    void manageCommand(byte* command);
    uint8_t getControlChangeValue(uint8_t index);
    uint8_t getNoteValue(uint8_t index);
    uint8_t assignFreePin();
    boolean contains(uint8_t value);
};
#endif

