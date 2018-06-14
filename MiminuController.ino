#include <SoftwareSerial.h>
#include <Commons.h>
#include "Menu.h"
#include "MidiKeyboard.h"
#include "Bluetooth.h"

Settings settings;
MidiKeyboard keyboard;
Menu menu;
Bluetooth bluetooth;

Led led(13, false);
char* data;

void setup() {
  settings.setup();
  keyboard.setup(&settings, &led);
  menu.setup(&settings, &led);
  bluetooth.setup();
}

void loop() {
  menu.loop();
  keyboard.loop();
  bluetooth.loop();
  if (bluetooth.isReceived()) {
    data = bluetooth.getData();
    menu.command(data);
    keyboard.command(data);
  }
}

