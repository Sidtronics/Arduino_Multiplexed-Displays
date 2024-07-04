#ifndef M_DISPLAY_H
#define M_DISPLAY_H
// M_Display.h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "../DisplayFont.h"
#include "../fonts/Fonts.h"
#include "MD_config.h"
#include "MD_settings.h"

// flags for state and direction.
#define ON true
#define OFF false
#define LEFT true
#define RIGHT false

class M_Display : public Print {

public:
  void mode(byte mode);
  void setDisplay(bool isOn, byte intensity = 7);
  void clear();
  void toggleLed(byte led);
  void setLed(bool isOn, byte led);
  virtual void toggleSeg(byte seg, byte digit) = 0;
  virtual void setSeg(bool isOn, byte seg, byte digit) = 0;
  void scroll(bool dir, byte len = 1);

protected:
  M_Display(

      const byte _stb, const byte _clk, const byte _data,
      const HMD_config &_config, byte (*_getFont)(char));

  M_Display(

      const byte _stb, const byte _clk, const byte _data,
      const VMD_config &_config, byte (*_getFont)(char));

  void sendCmd(byte cmd);
  void sendData(byte addr, byte dat);
  size_t write(byte chr) override;
  size_t write(const byte *buf, size_t size) override;
  void updateFrame();
  void update();

  virtual void writeDigit(byte digit, byte data) = 0;

  // display ram buffer:
  byte buffer[MD_DISPLAY_RAM_SIZE] = {0};

  const DisplayFont FONT;

private:

  // config:
  const byte TOTAL_DIGITS;
  const byte *const &LED_ADDR;
  const byte *const &LED_VAL;

  // print system:
  byte str_buffer[MD_STRING_BUFFER_SIZE] = {0};
  byte cursor_pos = 0;
  byte frame_beg = 0;

  // 3 wire serial: 
  const byte stb;
  const byte clk;
  const byte data;
};

#endif
