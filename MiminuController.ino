#include <Commons.h>
#include "Menu.h"
#include "MidiKeyboard.h"

Settings settings;
MidiKeyboard keyboard;
Menu menu;

Led led(13, false);

void setup() {
  settings.setup();
  keyboard.setup(&settings, &led);
  menu.setup(&settings, &led);
}

void loop() {
  menu.loop();
  keyboard.loop();
}
