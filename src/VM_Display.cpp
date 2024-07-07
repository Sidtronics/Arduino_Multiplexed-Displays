#include "VM_Display.h"

VM_Display::VM_Display(const uint8_t _stb, const uint8_t _clk,
                       const uint8_t _data, const VMD_config &_config,
                       uint8_t (*_getFont)(char))
    : M_Display(_stb, _clk, _data, _config, _getFont),
      DIGIT_BITPOS(_config.DIGIT_BITPOS), SEG_ADDR(_config.SEG_ADDR) {}

void VM_Display::setSeg(bool isOn, uint8_t seg, uint8_t digit) {

  if (isOn) {
    ram_buffer[SEG_ADDR[digit][seg]] |= bit(DIGIT_BITPOS[digit]);
    _send_data(SEG_ADDR[digit][seg], ram_buffer[SEG_ADDR[digit][seg]]);
  } else {
    ram_buffer[SEG_ADDR[digit][seg]] &= (0xFF - bit(DIGIT_BITPOS[digit]));
    _send_data(SEG_ADDR[digit][seg], ram_buffer[SEG_ADDR[digit][seg]]);
  }
}

void VM_Display::toggleSeg(uint8_t seg, uint8_t digit) {

  ram_buffer[SEG_ADDR[digit][seg]] ^= bit(DIGIT_BITPOS[digit]);
  _send_data(SEG_ADDR[digit][seg], ram_buffer[SEG_ADDR[digit][seg]]);
}

void VM_Display::writeDigit(uint8_t digit, uint8_t data) {

  for (int i = 0; i < 7; i++)
    bitWrite(ram_buffer[SEG_ADDR[digit][i]], DIGIT_BITPOS[digit],
             bitRead(getFont(data), i));
}
