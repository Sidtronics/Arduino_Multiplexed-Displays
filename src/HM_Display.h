#ifndef HM_DISPLAY_H
#define HM_DISPLAY_H

#include "main/M_Display.h"

class HM_Display : public M_Display {

public:
  HM_Display(const byte _stb, const byte _clk, const byte _data,
             const HMD_config &_config, byte (*_getFont)(char) = DefaultFont);

  void setSeg(bool isOn, byte seg, byte digit) override;
  void toggleSeg(byte seg, byte digit) override;

protected:
  void writeDigit(byte digit, byte data) override;

  const byte *const DIGIT_ADDR;
};

#endif
