#include "Settings.h"

const uint8_t MIN_CHANNEL_VALUE = 1;
const uint8_t MAX_CHANNEL_VALUE = 16;
const int8_t MIN_TRANSPOSITION_VALUE = -3;
const int8_t MAX_TRANSPOSITION_VALUE = 3;

int eepromAddress = 0;

struct Memory {
  boolean isModeCc;
  uint8_t channel;
  int8_t octave;
};

Settings::Settings() {}

void Settings::setup() {
  Memory memory;
  EEPROM.get(eepromAddress, memory);
  _isModeCc = memory.isModeCc;
  _channel = memory.channel;
  _octave = memory.octave;
}

boolean Settings::isModeCc() {
  return _isModeCc;
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

void Settings::toogleMode() {
  _isModeCc = !_isModeCc;
}

void Settings::up() {
  if (_isModeCc) {
    _channel = _channel < MAX_CHANNEL_VALUE ? _channel + 1 : _channel;
  } else {
    _octave = _octave < MAX_TRANSPOSITION_VALUE ? _octave + 1 : _octave;
  }
}

void Settings::down() {
  if (_isModeCc) {
    _channel = _channel > MIN_CHANNEL_VALUE ? _channel - 1 : _channel;
  } else {
    _octave = _octave > MIN_TRANSPOSITION_VALUE ? _octave - 1 : _octave;
  }
}

void Settings::save() {
  Memory memory = {
    _isModeCc,
    _channel,
    _octave
  };
  EEPROM.put(eepromAddress, memory);
}
