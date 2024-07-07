#ifndef M_DISPLAY_H
#define M_DISPLAY_H
// M_Display.h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdlib.h>

#include "../fonts/Fonts.h"
#include "MD_config.h"
#include "MD_settings.h"

// flags for display state.
#define ON true
#define OFF false

// flags for scroll direction.
#define LEFT true
#define RIGHT false

class M_Display : public Print {

public:
  void mode(uint8_t mode);
  void setDisplay(bool isOn, uint8_t intensity = 0);
  void init(uint8_t intensity = 0);
  void toggleLed(uint8_t led);
  void setLed(bool isOn, uint8_t led);
  void scroll(bool dir, uint8_t len = 1);
  void home();
  void end();
  void clear();
  void setCursor(uint8_t pos);

  virtual void toggleSeg(uint8_t seg, uint8_t digit) = 0;
  virtual void setSeg(bool isOn, uint8_t seg, uint8_t digit) = 0;
  virtual void writeDigit(uint8_t digit, uint8_t data) = 0;

protected:
  M_Display(

      const uint8_t _stb, const uint8_t _clk, const uint8_t _data,
      const HMD_config &_config, uint8_t (*_getFont)(char));

  M_Display(

      const uint8_t _stb, const uint8_t _clk, const uint8_t _data,
      const VMD_config &_config, uint8_t (*_getFont)(char));

  void _send_data(uint8_t addr, uint8_t dat);

  // display ram buffer:
  uint8_t ram_buffer[MD_DISPLAY_RAM_SIZE];

  uint8_t (*getFont)(char);

private:
  void _reset_print_system();
  uint8_t _clamp(int8_t val, int8_t min, int8_t max);
  void _send_cmd(uint8_t cmd);
  size_t write(uint8_t chr) override;
  size_t write(const uint8_t *buf, size_t size) override;
  void _update_frame();
  void _update_ram();

  // config:
  const uint8_t TOTAL_DIGITS;
  const uint8_t *const &LED_ADDR;
  const uint8_t *const &LED_VAL;

  // print system:
  uint8_t str_buffer[MD_STRING_BUFFER_SIZE];
  uint8_t cursor_pos;
  int8_t frame_beg;

  // 3 wire serial:
  const uint8_t stb;
  const uint8_t clk;
  const uint8_t data;
};

#endif
