#include "MidiController.h"

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
uint8_t bluetoothCommandValue;

MidiController::MidiController() {}

void MidiController::setup(Settings *settings, Led *led) {
  _settings = settings;
  _led = led;
  MIDI.begin(MIDI_CHANNEL_OMNI);
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    buttons[i] = new Button(assignFreePin(), 5);
  }
}

void MidiController::loop() {
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    buttonsState[i] = buttons[i]->state();
  }
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    midiButton(i);
  }
}

void MidiController::command(byte* command) {
  manageCommand(command);
}

void MidiController::midiButton(uint8_t index) {
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

void MidiController::manageCommand(byte* command) {
  bluetoothCommandIndex = command[0];
  bluetoothCommandValue = command[1];
  if (bluetoothCommandIndex >= 0 && bluetoothCommandIndex <= 39 && bluetoothCommandValue >= 0 && bluetoothCommandValue <= 127) {
    // Reserved for 40 Buttons
    if (_settings->isInModeCc()) {
      MIDI.sendControlChange(getControlChangeValue(bluetoothCommandIndex), bluetoothCommandValue, _settings->channel());
    } else {
      MIDI.sendNoteOn(getNoteValue(bluetoothCommandIndex), bluetoothCommandValue, _settings->channel());
    }
  } else if (bluetoothCommandIndex >= 100 && bluetoothCommandIndex <= 127 && bluetoothCommandValue >= 0 && bluetoothCommandValue <= 127) {
    // Reserved for 26 potentiometers
    MIDI.sendControlChange(getControlChangeValue(bluetoothCommandIndex), bluetoothCommandValue, _settings->channel());
  }
}

uint8_t MidiController::getControlChangeValue(uint8_t index) {
  return index;
}

uint8_t MidiController::getNoteValue(uint8_t index) {
  return index + MIDI_NOTE_START + _settings->transpose();
}

uint8_t MidiController::assignFreePin() {
  while(contains(lastAssignedPin)) {
    lastAssignedPin++;
  }
  if (lastAssignedPin >= LAST_ASSIGNABLE_PIN) {
    lastAssignedPin = LAST_ASSIGNABLE_PIN;
  }
  return lastAssignedPin++;
}

boolean MidiController::contains(uint8_t value) {
  for (uint8_t i = 0; i < ARRAY_LENGTH(NO_VALID_PINS); i++) {
    if (value == NO_VALID_PINS[i]) {
      return true;
    }
  }
  return false;
}

