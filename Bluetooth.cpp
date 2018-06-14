#include "Bluetooth.h"
#include <SoftwareSerial.h>

#define BT_RX 10
#define BT_TX 11
SoftwareSerial serialBluetooth(BT_RX, BT_TX);
const byte CHAR_AMOUNT = 32;
const char START_MARKER = '¡';
const char END_MARKER = '!';
boolean received = false;
boolean receiving = false;
char string[CHAR_AMOUNT];
byte index = 0;
char rc;

Bluetooth::Bluetooth() {}

void Bluetooth::setup() {
  serialBluetooth.begin(9600);
}

void Bluetooth::loop() {
  if (serialBluetooth.available() > 0 && received == false) {
    rc = serialBluetooth.read();
    if (receiving == true) {
      if (rc != END_MARKER) {
        string[index] = rc;
        index++;
        if (index >= CHAR_AMOUNT) {
          index = CHAR_AMOUNT - 1;
        }
      } else {
        string[index] = '\0'; // terminate the string
        index = 0;
        received = true;
        receiving = false;
      }
    } else if (rc == START_MARKER) {
      receiving = true;
    }
  }
}

boolean Bluetooth::isReceived() {
  return received;
}

char* Bluetooth::getData() {
  if (received == true) {
    received = false;
    return string;
  } else {
    return 0;
  }
}

