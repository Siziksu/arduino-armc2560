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
}

void Menu::loop() {
  for (uint8_t i = 0; i < NUM_MENU_BUTTONS; i++) {
    menuButtonsState[i] = menuButtons[i]->state();
  }
  for (uint8_t i = 0; i < NUM_MENU_BUTTONS; i++) {
    switch (menuButtonsState[i]) {
      case 1:
        _led->on();
        break;
      case 2:
        _led->off();
        if (menuButtons[i]->pin() == 2) {
          _settings->toogleEditMode();
          _screen.updateMenu();
        } else if (menuButtons[i]->pin() == 3) {
          _settings->up();
          _screen.updateMenu();
        } else if (menuButtons[i]->pin() == 4) {
          _settings->down();
          _screen.updateMenu();
        } else if (menuButtons[i]->pin() == 5) {
          _settings->save();
          _screen.showSettingsSaved();
        }
        break;
      default:
        break;
    }
  }
}
