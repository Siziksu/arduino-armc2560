#ifndef Menu_h
#define Menu_h

#include <Arduino.h>
#include <Commons.h>
#include "Settings.h"
#include "Screen.h"

class Menu {
  public:
    Menu();
    void setup(Settings *settings, Led *led);
    void loop();
    void edit();
    void up();
    void down();
    void save();
    void command(byte* command);
    
  private:
    Settings *_settings;
    Led *_led;
    Screen _screen;
};
#endif

