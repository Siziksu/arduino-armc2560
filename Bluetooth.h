#ifndef Bluetooth_h
#define Bluetooth_h

#include <Arduino.h>

class Bluetooth {
  public:
    Bluetooth();
    void setup();
    void loop();
    boolean isReceived();
    char* getData();
    
  private:
};
#endif

