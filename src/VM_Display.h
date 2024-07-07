#ifndef VM_DISPLAY_H
#define VM_DISPLAY_H

#include "main/M_Display.h"

class VM_Display : public M_Display {

public:
  VM_Display(const uint8_t _stb, const uint8_t _clk, const uint8_t _data,
             const VMD_config &_config,
             uint8_t (*_getFont)(char) = DefaultFont);

  void setSeg(bool isOn, uint8_t seg, uint8_t digit) override;
  void toggleSeg(uint8_t seg, uint8_t digit) override;
  void writeDigit(uint8_t digit, uint8_t data) override;

private:
  const uint8_t *const DIGIT_BITPOS;
  const uint8_t *const *const SEG_ADDR;
};

#endif
