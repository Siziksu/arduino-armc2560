#include "Bluetooth.h"
#include <SoftwareSerial.h>

#define BT_RX 10
#define BT_TX 11
SoftwareSerial serialBluetooth(BT_RX, BT_TX);
const byte PACKET_SIZE = 2;
const byte START_PACKET_BYTE = 254;
const byte END_PACKET_BYTE = 255;
bool received = false;
bool receiving = false;
byte result[PACKET_SIZE];
byte index = 0;
byte rc;

Bluetooth::Bluetooth() {}

void Bluetooth::setup() {
  serialBluetooth.begin(9600);
}

void Bluetooth::loop() {
  if (serialBluetooth.available() > 0 && received == false) {
    rc = serialBluetooth.read();
    if (receiving == true) {
      if (rc != END_PACKET_BYTE) {
        result[index] = rc;
        index++;
        if (index >= PACKET_SIZE) {
          index = PACKET_SIZE - 1;
        }
      } else {
        index = 0;
        received = true;
        receiving = false;
      }
    } else if (rc == START_PACKET_BYTE) {
      receiving = true;
    }
  }
}

bool Bluetooth::isReceived() {
  return received;
}

byte* Bluetooth::getData() {
  if (received == true) {
    received = false;
    return result;
  } else {
    return 0;
  }
}

