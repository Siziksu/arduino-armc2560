#include "Menu.h"

const uint8_t NUM_MENU_BUTTONS = 4;
const uint8_t MENU_PINS[] = {2, 3, 4, 5};

Button *menuButtons[NUM_MENU_BUTTONS];
uint8_t menuButtonsState[NUM_MENU_BUTTONS];

Menu::Menu() {}

void Menu::setup(Settings *settings, Led *led) {
  _settings = settings;
  _led = led;
  for (uint8_t i = 0; i < NUM_MENU_BUTTONS; i++) {
    menuButtons[i] = new Button(MENU_PINS[i], 5);
  }
  _screen.setup(_settings);
  _screen.showMode();
}

void Menu::loop() {
  for (uint8_t i = 0; i < NUM_MENU_BUTTONS; i++) {
    menuButtonsState[i] = menuButtons[i]->state();
  }
  for (uint8_t i = 0; i < NUM_MENU_BUTTONS; i++) {
    menuButton(i);
  }
}

void Menu::menuButton(uint8_t index) {
  switch (menuButtonsState[index]) {
    case 1:
      _led->on();
      break;
    case 2:
      _led->off();
      if (menuButtons[index]->pin() == 2) {
        _settings->toogleMode();
        _screen.showMode();
      } else if (menuButtons[index]->pin() == 3) {
        _settings->up();
        _screen.showMode();
      } else if (menuButtons[index]->pin() == 4) {
        _settings->down();
        _screen.showMode();
      } else if (menuButtons[index]->pin() == 5) {
        _settings->save();
        _screen.showSettingsSaved();
      }
      break;
    default:
      break;
  }
}
