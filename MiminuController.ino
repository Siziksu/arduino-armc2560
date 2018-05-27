#include <Commons.h>
#include <MIDI.h>
#include "Screen.h"
#include "Settings.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

MIDI_CREATE_DEFAULT_INSTANCE();

const uint8_t MIN_MIDI_VALUE = 0;
const uint8_t MAX_MIDI_VALUE = 127;
const uint8_t MIDI_NOTE_START = 36;
const uint8_t NUM_BUTTONS = 32;
const uint8_t MENU_BUTTONS = 4;
const uint8_t ARDUINO_MEGA_NO_VALID_DIGITAL_PINS[] = {0, 1, 14, 15, 16, 17, 18, 19, 20, 21};
const uint8_t ARDUINO_MEGA_LAST_DIGITAL_PIN = 53;

Screen screen;
Settings settings;
Led led(13, false);
Button *buttons[NUM_BUTTONS];
uint8_t buttonsState[NUM_BUTTONS];
uint8_t lastAssignedPin = 0;

void setup() {
  screen.setup();
  settings.setup();
  MIDI.begin(MIDI_CHANNEL_OMNI);
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = new Button(assignFreePin(), 5);
  }
  delay(1500);
  screen.clearScreen();
  screen.showMode(settings);
}

void loop() {
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    buttonsState[i] = buttons[i]->state();
  }
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    if (buttons[i]->pin() == 2 || buttons[i]->pin() == 3 ||  buttons[i]->pin() == 4 || buttons[i]->pin() == 5) {
      menuButton(i);
    } else {
      midiButton(i);
    }
  }
}

void menuButton(uint8_t i) {
  switch (buttonsState[i]) {
    case 2:
      if (buttons[i]->pin() == 2) {
        settings.toogleMode();
        screen.showMode(settings);
      } else if (buttons[i]->pin() == 3) {
        settings.up();
        screen.showMode(settings);
      } else if (buttons[i]->pin() == 4) {
        settings.down();
        screen.showMode(settings);
      } else if (buttons[i]->pin() == 5) {
        settings.save();
        screen.showSettingsSaved(settings);
      }
      break;
    default:
      break;
  }
}

void midiButton(uint8_t i) {
  switch (buttonsState[i]) {
    case 1:
      led.on();
      if (settings.isModeCc()) {
        MIDI.sendControlChange(getControlChangeValue(i), MAX_MIDI_VALUE, settings.channel());
      } else {
        MIDI.sendNoteOn(getNoteValue(i), MAX_MIDI_VALUE, settings.channel());
      }
      break;
    case 2:
      led.off();
      if (settings.isModeCc()) {
        MIDI.sendControlChange(getControlChangeValue(i), MIN_MIDI_VALUE, settings.channel());
      } else {
        MIDI.sendNoteOff(getNoteValue(i), MAX_MIDI_VALUE, settings.channel());
      }
      break;
    default:
      break;
  }
}

uint8_t getControlChangeValue(uint8_t index) {
  return index - MENU_BUTTONS;
}

uint8_t getNoteValue(uint8_t index) {
  return index - MENU_BUTTONS + MIDI_NOTE_START + settings.transpose();
}

uint8_t assignFreePin() {
  while(contains(lastAssignedPin)) {
    lastAssignedPin++;
  }
  if (lastAssignedPin >= ARDUINO_MEGA_LAST_DIGITAL_PIN) {
    lastAssignedPin = ARDUINO_MEGA_LAST_DIGITAL_PIN;
  }
  return lastAssignedPin++;
}

boolean contains(uint8_t value) {
  for (uint8_t i = 0; i < ARRAY_LENGTH(ARDUINO_MEGA_NO_VALID_DIGITAL_PINS); i++) {
    if (value == ARDUINO_MEGA_NO_VALID_DIGITAL_PINS[i]) {
      return true;
    }
  }
  return false;
}

