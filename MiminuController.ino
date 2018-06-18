#include <Commons.h>
#include "Menu.h"
#include "MidiController.h"
#include "Bluetooth.h"

Settings settings;
MidiController controller;
Menu menu;
Bluetooth bluetooth;

Led led(13, false);
byte* data;

void setup() {
  settings.setup();
  controller.setup(&settings, &led);
  menu.setup(&settings, &led);
  bluetooth.setup();
}

void loop() {
  menu.loop();
  controller.loop();
  bluetooth.loop();
  if (bluetooth.isReceived()) {
    data = bluetooth.getData();
    menu.command(data);
    controller.command(data);
  }
}

