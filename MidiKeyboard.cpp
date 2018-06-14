#include "MidiKeyboard.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

MIDI_CREATE_DEFAULT_INSTANCE();

const uint8_t NUM_BUTTONS = 28;
const uint8_t NO_VALID_PINS[] = {0, 1, 2, 3, 4, 5, 10, 11, 14, 15, 16, 17, 18, 19, 20, 21};
const uint8_t LAST_ASSIGNABLE_PIN = 53;
const uint8_t MIN_MIDI_VALUE = 0;
const uint8_t MAX_MIDI_VALUE = 127;
const uint8_t MIDI_NOTE_START = 48;

Button *buttons[NUM_BUTTONS];
uint8_t buttonsState[NUM_BUTTONS];
uint8_t lastAssignedPin = 0;

boolean bluetoothCommandState;
uint8_t bluetoothCommandIndex;
boolean bluettothCommandNotValid;

MidiKeyboard::MidiKeyboard() {}

void MidiKeyboard::setup(Settings *settings, Led *led) {
  _settings = settings;
  _led = led;
  MIDI.begin(MIDI_CHANNEL_OMNI);
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = new Button(assignFreePin(), 5);
  }
}

void MidiKeyboard::loop() {
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    buttonsState[i] = buttons[i]->state();
  }
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    midiButton(i);
  }
}

void MidiKeyboard::command(char* string) {
  manageCommand(string);
}

void MidiKeyboard::midiButton(uint8_t index) {
  switch (buttonsState[index]) {
    case 1:
      if (_settings->isInModeCc()) {
        MIDI.sendControlChange(getControlChangeValue(index), MAX_MIDI_VALUE, _settings->channel());
      } else {
        MIDI.sendNoteOn(getNoteValue(index), MAX_MIDI_VALUE, _settings->channel());
      }
      break;
    case 2:
      if (_settings->isInModeCc()) {
        MIDI.sendControlChange(getControlChangeValue(index), MIN_MIDI_VALUE, _settings->channel());
      } else {
        MIDI.sendNoteOff(getNoteValue(index), MAX_MIDI_VALUE, _settings->channel());
      }
      break;
    default:
      break;
  }
}

uint8_t MidiKeyboard::getControlChangeValue(uint8_t index) {
  return index;
}

uint8_t MidiKeyboard::getNoteValue(uint8_t index) {
  return index + MIDI_NOTE_START + _settings->transpose();
}

uint8_t MidiKeyboard::assignFreePin() {
  while(contains(lastAssignedPin)) {
    lastAssignedPin++;
  }
  if (lastAssignedPin >= LAST_ASSIGNABLE_PIN) {
    lastAssignedPin = LAST_ASSIGNABLE_PIN;
  }
  return lastAssignedPin++;
}

boolean MidiKeyboard::contains(uint8_t value) {
  for (uint8_t i = 0; i < ARRAY_LENGTH(NO_VALID_PINS); i++) {
    if (value == NO_VALID_PINS[i]) {
      return true;
    }
  }
  return false;
}

void MidiKeyboard::manageCommand(char* string) {
  bluettothCommandNotValid = false;
  if (strcmp(string, "MIDI 0 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 0;
  } else if (strcmp(string, "MIDI 0 OFF") == 0) {
    bluetoothCommandState= false;
    bluetoothCommandIndex = 0;
  } else if (strcmp(string, "MIDI 1 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 1;
  } else if (strcmp(string, "MIDI 1 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 1;
  } else if (strcmp(string, "MIDI 2 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 2;
  } else if (strcmp(string, "MIDI 2 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 2;
  } else if (strcmp(string, "MIDI 3 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 3;
  } else if (strcmp(string, "MIDI 3 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 3;
  } else if (strcmp(string, "MIDI 4 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 4;
  } else if (strcmp(string, "MIDI 4 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 4;
  } else if (strcmp(string, "MIDI 5 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 5;
  } else if (strcmp(string, "MIDI 5 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 5;
  } else if (strcmp(string, "MIDI 6 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 6;
  } else if (strcmp(string, "MIDI 6 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 6;
  } else if (strcmp(string, "MIDI 7 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 7;
  } else if (strcmp(string, "MIDI 7 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 7;
  } else if (strcmp(string, "MIDI 8 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 8;
  } else if (strcmp(string, "MIDI 8 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 8;
  } else if (strcmp(string, "MIDI 9 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 9;
  } else if (strcmp(string, "MIDI 9 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 9;
  } else if (strcmp(string, "MIDI 10 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 10;
  } else if (strcmp(string, "MIDI 10 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 10;
  } else if (strcmp(string, "MIDI 11 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 11;
  } else if (strcmp(string, "MIDI 11 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 11;
  } else if (strcmp(string, "MIDI 12 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 12;
  } else if (strcmp(string, "MIDI 12 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 12;
  } else if (strcmp(string, "MIDI 13 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 13;
  } else if (strcmp(string, "MIDI 13 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 13;
  } else if (strcmp(string, "MIDI 14 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 14;
  } else if (strcmp(string, "MIDI 14 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 14;
  } else if (strcmp(string, "MIDI 15 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 15;
  } else if (strcmp(string, "MIDI 15 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 15;
  } else if (strcmp(string, "MIDI 16 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 16;
  } else if (strcmp(string, "MIDI 16 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 16;
  } else if (strcmp(string, "MIDI 17 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 17;
  } else if (strcmp(string, "MIDI 17 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 17;
  } else if (strcmp(string, "MIDI 18 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 18;
  } else if (strcmp(string, "MIDI 18 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 18;
  } else if (strcmp(string, "MIDI 19 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 19;
  } else if (strcmp(string, "MIDI 19 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 19;
  } else if (strcmp(string, "MIDI 20 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 20;
  } else if (strcmp(string, "MIDI 20 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 20;
  } else if (strcmp(string, "MIDI 21 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 21;
  } else if (strcmp(string, "MIDI 21 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 21;
  } else if (strcmp(string, "MIDI 22 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 22;
  } else if (strcmp(string, "MIDI 22 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 22;
  } else if (strcmp(string, "MIDI 23 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 23;
  } else if (strcmp(string, "MIDI 23 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 23;
  } else if (strcmp(string, "MIDI 24 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 24;
  } else if (strcmp(string, "MIDI 24 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 24;
  } else if (strcmp(string, "MIDI 25 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 25;
  } else if (strcmp(string, "MIDI 25 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 25;
  } else if (strcmp(string, "MIDI 26 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 26;
  } else if (strcmp(string, "MIDI 26 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 26;
  } else if (strcmp(string, "MIDI 27 ON") == 0) {
    bluetoothCommandState = true;
    bluetoothCommandIndex = 27;
  } else if (strcmp(string, "MIDI 27 OFF") == 0) {
    bluetoothCommandState = false;
    bluetoothCommandIndex = 27;
  } else {
    bluettothCommandNotValid = true;
  }
  if (!bluettothCommandNotValid) {
    switch (bluetoothCommandState) {
      case true:
        if (_settings->isInModeCc()) {
          MIDI.sendControlChange(getControlChangeValue(bluetoothCommandIndex), MAX_MIDI_VALUE, _settings->channel());
        } else {
          MIDI.sendNoteOn(getNoteValue(bluetoothCommandIndex), MAX_MIDI_VALUE, _settings->channel());
        }
        break;
      case false:
        if (_settings->isInModeCc()) {
          MIDI.sendControlChange(getControlChangeValue(bluetoothCommandIndex), MIN_MIDI_VALUE, _settings->channel());
        } else {
          MIDI.sendNoteOff(getNoteValue(bluetoothCommandIndex), MAX_MIDI_VALUE, _settings->channel());
        }
        break;
      default:
        break;
    }
  }
}

