#ifndef HM_DISPLAY_H
#define HM_DISPLAY_H

#include "main/M_Display.h"

class HM_Display : public M_Display {

public:
  HM_Display(const uint8_t _stb, const uint8_t _clk, const uint8_t _data,
             const HMD_config &_config,
             uint8_t (*_getFont)(char) = DefaultFont);

  void setSeg(bool isOn, uint8_t seg, uint8_t digit) override;
  void toggleSeg(uint8_t seg, uint8_t digit) override;
  void writeDigit(uint8_t digit, uint8_t data) override;

private:
  const uint8_t *const DIGIT_ADDR;
};

#endif
