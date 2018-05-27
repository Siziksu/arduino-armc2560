#include "Screen.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Screen::Screen() {}

void Screen::setup() {
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
}

void Screen::showMode(Settings settings) {
  if (settings.isModeCc()) {
    showCcMode(settings.channel());
  } else {
    showNoteMode(settings.octave());
  }
}

void Screen::showSettingsSaved(Settings settings) {
  showSettingsSaved();
  delay(1500);
  showMode(settings);
}

void Screen::showCcMode(uint8_t channel) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("CC MODE");
  display.setTextSize(1);
  display.print("CHANNEL: ");
  display.println(channel);
  display.display();
}

void Screen::showNoteMode(int8_t octave) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("NOTE MODE");
  display.setTextSize(1);
  display.print("TRANSPOSE: ");
  display.println(octave);
  display.display();
}

void Screen::showSettingsSaved() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("SETTINGS");
  display.setTextSize(1);
  display.println("SAVED");
  display.display();
}

