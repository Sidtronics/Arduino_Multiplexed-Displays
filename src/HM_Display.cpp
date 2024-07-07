#include "HM_Display.h"

HM_Display::HM_Display(const uint8_t _stb, const uint8_t _clk,
                       const uint8_t _data, const HMD_config &_config,
                       uint8_t (*_getFont)(char))
    : M_Display(_stb, _clk, _data, _config, _getFont),
      DIGIT_ADDR(_config.DIGIT_ADDR) {}

void HM_Display::setSeg(bool isOn, uint8_t seg, uint8_t digit) {

  if (isOn) {
    ram_buffer[DIGIT_ADDR[digit]] |= bit(seg);
    _send_data(DIGIT_ADDR[digit], ram_buffer[DIGIT_ADDR[digit]]);
  } else {
    ram_buffer[DIGIT_ADDR[digit]] &= (0xFF - bit(seg));
    _send_data(DIGIT_ADDR[digit], ram_buffer[DIGIT_ADDR[digit]]);
  }
}

void HM_Display::toggleSeg(uint8_t seg, uint8_t digit) {

  ram_buffer[DIGIT_ADDR[digit]] ^= bit(seg);
  _send_data(DIGIT_ADDR[digit], ram_buffer[DIGIT_ADDR[digit]]);
}

void HM_Display::writeDigit(uint8_t digit, uint8_t data) {

  ram_buffer[DIGIT_ADDR[digit]] =
      (ram_buffer[DIGIT_ADDR[digit]] & 0x80) | getFont(data);
}
