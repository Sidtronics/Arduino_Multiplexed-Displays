#include "M_Display.h"

M_Display::M_Display(

    const byte _stb, const byte _clk, const byte _data,
    const HMD_config &_config, byte (*_getFont)(char))
    :

      stb(_stb), clk(_clk), data(_data), TOTAL_DIGITS(_config.TOTAL_DIGITS),
      LED_ADDR(_config.LED_ADDR), LED_VAL(_config.LED_VAL), FONT(_getFont)

{
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(stb, HIGH);
  digitalWrite(clk, LOW);
}

M_Display::M_Display(

    const byte _stb, const byte _clk, const byte _data,
    const VMD_config &_config, byte (*_getFont)(char))
    :

      stb(_stb), clk(_clk), data(_data), TOTAL_DIGITS(_config.TOTAL_DIGITS),
      LED_ADDR(_config.LED_ADDR), LED_VAL(_config.LED_VAL), FONT(_getFont)

{
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);

  digitalWrite(stb, HIGH);
  digitalWrite(clk, LOW);
}

void M_Display::sendCmd(byte cmd) {

  delay(1);
  digitalWrite(clk, LOW);
  digitalWrite(stb, LOW);
  shiftOut(data, clk, LSBFIRST, cmd);
  delayMicroseconds(10);
  digitalWrite(stb, HIGH);
  delay(1);
}

void M_Display::sendData(byte addr, byte dat) {

  delay(1);
  digitalWrite(clk, LOW);
  digitalWrite(stb, LOW);
  shiftOut(data, clk, LSBFIRST, MD_CMD_ADDR_SETTING | addr);
  shiftOut(data, clk, LSBFIRST, dat);
  delayMicroseconds(10);
  digitalWrite(stb, HIGH);
  delay(1);
}

void M_Display::mode(byte mode) { sendCmd(MD_CMD_MODE_SETTING | mode); }

void M_Display::setDisplay(bool isOn, byte intensity) {

  sendCmd(MD_CMD_DISPLAY_CONTROL | (isOn ? MD_FLG_ON : MD_FLG_OFF) |
          min(7, intensity));
}

void M_Display::clear() {

  for (int i = 0; i < MD_DISPLAY_RAM_SIZE; i++)
    buffer[i] = 0x00;

  cursor_pos = 0;
  frame_beg = 0;

  update();
}

void M_Display::update() {

  sendCmd(MD_CMD_DATA_SETTING | MD_FLG_NORMAL_OP | MD_FLG_INCREMENTAL_ADDR |
          MD_FLG_WRITE);
  digitalWrite(clk, LOW);
  digitalWrite(stb, LOW);
  shiftOut(data, clk, LSBFIRST, MD_CMD_ADDR_SETTING | 0x00);

  for (int i = 0; i < MD_DISPLAY_RAM_SIZE; i++)
    shiftOut(data, clk, LSBFIRST, buffer[i]);

  delayMicroseconds(10);
  digitalWrite(stb, HIGH);
  delay(1);
}

size_t M_Display::write(byte chr) {

  if (cursor_pos == MD_STRING_BUFFER_SIZE)
    return 0;

  str_buffer[cursor_pos] = chr;

  if (cursor_pos >= frame_beg && cursor_pos < frame_beg + TOTAL_DIGITS)
    updateFrame();

  cursor_pos++;

  return 1;
}

size_t M_Display::write(const byte *buf, size_t size) {

  if (cursor_pos == MD_STRING_BUFFER_SIZE)
    return 0;

  byte n = size < MD_STRING_BUFFER_SIZE - cursor_pos
               ? size
               : MD_STRING_BUFFER_SIZE - cursor_pos;

  memcpy(str_buffer + cursor_pos, buf, n);

  if (!(cursor_pos + n <= frame_beg || frame_beg + TOTAL_DIGITS <= cursor_pos))
    updateFrame();

  cursor_pos += size;

  return n;
}

void M_Display::updateFrame() {

  for (int i = 0; i < TOTAL_DIGITS; ++i) {

    if (i + frame_beg < 0 || i + frame_beg >= MD_STRING_BUFFER_SIZE)
      writeDigit(i, ' ');
    else
      writeDigit(i, str_buffer[frame_beg + i]);
  }

  update();
}

void M_Display::scroll(bool dir, byte len) {

  dir ? frame_beg += len : frame_beg -= len;

  if (frame_beg < -MD_STRING_BUFFER_SIZE)
    frame_beg = -MD_STRING_BUFFER_SIZE;

  else if (frame_beg > MD_STRING_BUFFER_SIZE)
    frame_beg = MD_STRING_BUFFER_SIZE;

  updateFrame();
}

void M_Display::toggleLed(byte led) {

  buffer[LED_ADDR[led]] ^= LED_VAL[led];
  sendData(LED_ADDR[led], buffer[LED_ADDR[led]]);
}

void M_Display::setLed(bool isOn, byte led) {

  if (isOn) {

    buffer[LED_ADDR[led]] |= LED_VAL[led];
    sendData(LED_ADDR[led], buffer[LED_ADDR[led]]);

  } else {

    buffer[LED_ADDR[led]] &= (0xFF - LED_VAL[led]);
    sendData(LED_ADDR[led], buffer[LED_ADDR[led]]);
  }
}
