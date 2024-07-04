#ifndef MD_CONFIG_STRUCTS_H
#define MD_CONFIG_STRUCTS_H

struct HMD_config {

  const byte TOTAL_DIGITS;
  const byte *LED_ADDR;
  const byte *LED_VAL;

  const byte *DIGIT_ADDR;
};

struct VMD_config {

  const byte TOTAL_DIGITS;
  const byte *LED_ADDR;
  const byte *LED_VAL;

  const byte *DIGIT_BITPOS;
  const byte **SEG_ADDR;
};

#endif
