#include "M_Display.h"

M_Display::M_Display(

    const uint8_t _stb, const uint8_t _clk, const uint8_t _data,
    const HMD_config &_config, uint8_t (*_getFont)(char))
    :

      stb(_stb), clk(_clk), data(_data), TOTAL_DIGITS(_config.TOTAL_DIGITS),
      LED_ADDR(_config.LED_ADDR), LED_VAL(_config.LED_VAL), getFont(_getFont)

{
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(stb, HIGH);
  digitalWrite(clk, LOW);
}

M_Display::M_Display(

    const uint8_t _stb, const uint8_t _clk, const uint8_t _data,
    const VMD_config &_config, uint8_t (*_getFont)(char))
    :

      stb(_stb), clk(_clk), data(_data), TOTAL_DIGITS(_config.TOTAL_DIGITS),
      LED_ADDR(_config.LED_ADDR), LED_VAL(_config.LED_VAL), getFont(_getFont)

{
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(stb, HIGH);
  digitalWrite(clk, LOW);
}

void M_Display::_send_cmd(uint8_t cmd) {

  delay(1);
  digitalWrite(clk, LOW);
  digitalWrite(stb, LOW);
  shiftOut(data, clk, LSBFIRST, cmd);
  delayMicroseconds(10);
  digitalWrite(stb, HIGH);
  delay(1);
}

void M_Display::_send_data(uint8_t addr, uint8_t dat) {

  delay(1);
  digitalWrite(clk, LOW);
  digitalWrite(stb, LOW);
  shiftOut(data, clk, LSBFIRST, MD_CMD_ADDR_SETTING | addr);
  shiftOut(data, clk, LSBFIRST, dat);
  delayMicroseconds(10);
  digitalWrite(stb, HIGH);
  delay(1);
}

void M_Display::mode(uint8_t mode) { _send_cmd(MD_CMD_MODE_SETTING | mode); }

void M_Display::setDisplay(bool isOn, uint8_t intensity) {

  _send_cmd(MD_CMD_DISPLAY_CONTROL | (isOn ? MD_FLG_ON : MD_FLG_OFF) |
            (intensity > 7 ? 7 : intensity));
}

void M_Display::init(uint8_t intensity) {

  memset(ram_buffer, 0, MD_DISPLAY_RAM_SIZE);
  _reset_print_system();

  setDisplay(true, intensity);
  _update_ram();
}

void M_Display::_update_ram() {

  _send_cmd(MD_CMD_DATA_SETTING | MD_FLG_NORMAL_OP | MD_FLG_INCREMENTAL_ADDR |
            MD_FLG_WRITE);
  digitalWrite(clk, LOW);
  digitalWrite(stb, LOW);
  shiftOut(data, clk, LSBFIRST, MD_CMD_ADDR_SETTING | 0x00);

  for (int i = 0; i < MD_DISPLAY_RAM_SIZE; i++)
    shiftOut(data, clk, LSBFIRST, ram_buffer[i]);

  delayMicroseconds(10);
  digitalWrite(stb, HIGH);
  delay(1);
}

size_t M_Display::write(uint8_t chr) {

  if (cursor_pos == MD_STRING_BUFFER_SIZE)
    return 0;

  str_buffer[cursor_pos] = chr;

  if (cursor_pos >= frame_beg && cursor_pos < frame_beg + TOTAL_DIGITS)
    _update_frame();

  cursor_pos++;

  return 1;
}

size_t M_Display::write(const uint8_t *buf, size_t size) {

  if (cursor_pos == MD_STRING_BUFFER_SIZE)
    return 0;

  uint8_t n = size < MD_STRING_BUFFER_SIZE - cursor_pos
                  ? size
                  : MD_STRING_BUFFER_SIZE - cursor_pos;

  memcpy(str_buffer + cursor_pos, buf, n);

  if (!(cursor_pos + n <= frame_beg || frame_beg + TOTAL_DIGITS <= cursor_pos))
    _update_frame();

  cursor_pos += size;

  return n;
}

void M_Display::_update_frame() {

  for (int i = 0; i < TOTAL_DIGITS; ++i) {

    if (i + frame_beg < 0 || i + frame_beg >= MD_STRING_BUFFER_SIZE)
      writeDigit(i, ' ');
    else
      writeDigit(i, str_buffer[frame_beg + i]);
  }

  _update_ram();
}

void M_Display::scroll(bool dir, uint8_t len) {

  dir ? frame_beg += len : frame_beg -= len;
  frame_beg = _clamp(frame_beg, -TOTAL_DIGITS, MD_STRING_BUFFER_SIZE);
  _update_frame();
}

void M_Display::home() {

  frame_beg = 0;
  _update_frame();
}

void M_Display::end() {

  frame_beg = MD_STRING_BUFFER_SIZE - TOTAL_DIGITS;
  _update_frame();
}

void M_Display::clear() {

  _reset_print_system();
  _update_frame();
}

void M_Display::setCursor(uint8_t pos) {

  cursor_pos = _clamp(pos, 0, MD_STRING_BUFFER_SIZE);
}

void M_Display::toggleLed(uint8_t led) {

  ram_buffer[LED_ADDR[led]] ^= LED_VAL[led];
  _send_data(LED_ADDR[led], ram_buffer[LED_ADDR[led]]);
}

void M_Display::setLed(bool isOn, uint8_t led) {

  if (isOn) {

    ram_buffer[LED_ADDR[led]] |= LED_VAL[led];
    _send_data(LED_ADDR[led], ram_buffer[LED_ADDR[led]]);

  } else {

    ram_buffer[LED_ADDR[led]] &= (0xFF - LED_VAL[led]);
    _send_data(LED_ADDR[led], ram_buffer[LED_ADDR[led]]);
  }
}

void M_Display::_reset_print_system() {

  memset(str_buffer, 0, MD_STRING_BUFFER_SIZE);

  cursor_pos = 0;
  frame_beg = 0;
}

uint8_t M_Display::_clamp(int8_t val, int8_t min, int8_t max) {

  if (val < min)
    return min;
  else if (val > max)
    return max;
  else
    return val;
}
