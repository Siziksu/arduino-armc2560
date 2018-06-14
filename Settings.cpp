#include "Settings.h"

const uint8_t MIN_CHANNEL_VALUE = 1;
const uint8_t MAX_CHANNEL_VALUE = 16;
const int8_t MIN_TRANSPOSITION_VALUE = -3;
const int8_t MAX_TRANSPOSITION_VALUE = 3;

int eepromAddress = 0;

struct Memory {
  boolean modeCc;
  uint8_t channel;
  int8_t octave;
};

Settings::Settings() {}

void Settings::toogleEditMode() {
  _editMode = !_editMode;
}

void Settings::setup() {
  Memory memory;
  EEPROM.get(eepromAddress, memory);
  _modeCc = memory.modeCc;
  _channel = memory.channel;
  _octave = memory.octave;
}

void Settings::up() {
  if (!_editMode) {
    _menuOption = _menuOption > 1 ? _menuOption - 1 : _menuOption;
  } else {
    switch(_menuOption) {
      case 1:
        _modeCc = !_modeCc;
        break;
      case 2:
        _channel = _channel < 16 ? _channel + 1 : _channel;
        break;
      case 3:
        _octave = _octave < 3 ? _octave + 1 : _octave;
        break;
    }
  }
}

void Settings::down() {
  if (!_editMode) {
    _menuOption = _menuOption < 3 ? _menuOption + 1 : _menuOption;
  } else {
    switch(_menuOption) {
      case 1:
        _modeCc = !_modeCc;
        break;
      case 2:
        _channel = _channel > 1 ? _channel - 1 : _channel;
        break;
      case 3:
        _octave = _octave > -3 ? _octave - 1 : _octave;
        break;
    }
  }
}

void Settings::save() {
  Memory memory = {
    _modeCc,
    _channel,
    _octave
  };
  EEPROM.put(eepromAddress, memory);
}

boolean Settings::isInEditMode() {
  return _editMode;
}

uint8_t Settings::menuOption() {
  return _menuOption;
}

boolean Settings::isInModeCc() {
  return _modeCc;
}

uint8_t Settings::channel() {
  return _channel;
}

int8_t Settings::octave() {
  return _octave;
}

int8_t Settings::transpose() {
  return _octave * 12;
}

