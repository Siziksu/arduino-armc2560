#include "Screen.h"

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

const uint8_t LINE_HEIGHT = 8;
const uint8_t CHAR_WIDTH = 6;
const uint8_t CHAR_HALF_WIDTH = 3;

Screen::Screen() {}

void Screen::setup(Settings *settings) {
  _settings = settings;
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showLogo();
}

void Screen::clearScreen() {
  display.clearDisplay();
  display.display();
}

void Screen::showLogo() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 8, LINE_HEIGHT * 1);
  display.print("MIMINU");
  display.setCursor(CHAR_WIDTH * 6, LINE_HEIGHT * 2);
  display.print("CONTROLLER");
  display.setCursor(CHAR_WIDTH * 9 + CHAR_HALF_WIDTH, LINE_HEIGHT * 3);
  display.print("1.0");
  display.display();
  delay(1500);
  drawMenu();
}

void Screen::drawMenu() {
  updateMenu();
}

void Screen::updateMenu() {
  display.clearDisplay();
  
  display.setTextSize(1);
  
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 4, LINE_HEIGHT * 1);
  display.print("MODE     :");
  if (_settings->isInEditMode() && _settings->menuOption() == 1) {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(" ");
  display.print(_settings->isInModeCc() ? "CC" : "NOTE");
  display.print(" ");
  
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 4, LINE_HEIGHT * 2);
  display.print("CHANNEL  :");
  if (_settings->isInEditMode() && _settings->menuOption() == 2) {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(" ");
  display.print(_settings->channel());
  display.print(" ");
  
  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 4, LINE_HEIGHT * 3);
  display.print("TRANSPOSE:");
  if (_settings->isInEditMode() && _settings->menuOption() == 3) {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(" ");
  if (_settings->octave() > 0) {
    display.print("+");
  }
  display.print(_settings->octave());
  display.print(" ");

  display.setTextColor(WHITE);
  display.setCursor(CHAR_WIDTH * 2, LINE_HEIGHT * _settings->menuOption());
  display.write(175);

  display.display();
}

void Screen::showSettingsSaved() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(CHAR_WIDTH * 7, LINE_HEIGHT * 2);
  display.print("SETTINGS");
  display.setCursor(CHAR_WIDTH * 8 + CHAR_HALF_WIDTH, LINE_HEIGHT * 3);
  display.print("SAVED");
  display.display();
  delay(1500);
  drawMenu();
}
