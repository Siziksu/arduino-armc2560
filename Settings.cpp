#include <EEPROM.h>
#include "Settings.h"

int address = 0;

struct Memory {
  boolean isModeCc;
  uint8_t channel;
  int8_t octave;
};

Settings::Settings() {}

void Settings::setup() {
  Memory memory;
  EEPROM.get(address, memory);
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
    _channel = _channel <= 15 ? _channel + 1 : _channel;
  } else {
    _octave = _octave <= 2 ? _octave + 1 : _octave;
  }
}

void Settings::down() {
  if (_isModeCc) {
    _channel = _channel >= 2 ? _channel - 1 : _channel;
  } else {
    _octave = _octave >= -2 ? _octave - 1 : _octave;
  }
}

void Settings::save() {
  Memory memory = {
    _isModeCc,
    _channel,
    _octave
  };
  EEPROM.put(address, memory);
}

