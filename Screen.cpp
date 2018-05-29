#include "Screen.h"

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

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
  display.drawRect(0, 0, 128,32, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("        MIMINU");
  display.println("      CONTROLLER");
  display.println("         1.0");
  display.display();
  delay(1500);
}

void Screen::showMode() {
  if (_settings->isModeCc()) {
    showCcMode(_settings->channel());
  } else {
    showNoteMode(_settings->octave());
  }
}

void Screen::showSettingsSaved() {
  showMessage("SETTINGS", 2, "SAVED", 1);
  delay(1500);
  showMode();
}

void Screen::showCcMode(uint8_t channel) {
  String prefix = "CHANNEL: ";
  showMessage("CC MODE", 2, (channel == 0 ? prefix += "OMNI" : prefix += channel), 1);
}

void Screen::showNoteMode(int8_t octave) {
  String prefix = "TRANSPOSE: ";
  showMessage("NOTE MODE", 2, prefix + octave, 1);
}

void Screen::showMessage(String line1, int8_t size1, String line2, int8_t size2) {
  display.clearDisplay();
  display.setCursor(0, 5);
  display.setTextColor(WHITE);
  display.setTextSize(size1);
  display.println(line1);
  display.setTextSize(size2);
  display.println(line2);
  display.display();
}
