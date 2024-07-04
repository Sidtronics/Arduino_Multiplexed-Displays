#include "HM_Display.h"

HM_Display::HM_Display(const byte _stb, const byte _clk, const byte _data,
                       const HMD_config &_config, byte (*_getFont)(char))
    : M_Display(_stb, _clk, _data, _config, _getFont),
      DIGIT_ADDR(_config.DIGIT_ADDR) {}

void HM_Display::setSeg(bool isOn, byte seg, byte digit) {

  if (isOn) {
    buffer[DIGIT_ADDR[digit]] |= bit(seg);
    sendData(DIGIT_ADDR[digit], buffer[DIGIT_ADDR[digit]]);
  } else {
    buffer[DIGIT_ADDR[digit]] &= (0xFF - bit(seg));
    sendData(DIGIT_ADDR[digit], buffer[DIGIT_ADDR[digit]]);
  }
}

void HM_Display::toggleSeg(byte seg, byte digit) {

  buffer[DIGIT_ADDR[digit]] ^= bit(seg);
  sendData(DIGIT_ADDR[digit], buffer[DIGIT_ADDR[digit]]);
}

void HM_Display::writeDigit(byte digit, byte data) {

  buffer[DIGIT_ADDR[digit]] = (buffer[DIGIT_ADDR[digit]] & 0x80) | FONT[data];
}
