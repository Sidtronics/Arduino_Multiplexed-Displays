#ifndef MD_CONFIG_STRUCTS_H
#define MD_CONFIG_STRUCTS_H

#include <stdint.h>

struct HMD_config {

  const uint8_t TOTAL_DIGITS;
  const uint8_t *LED_ADDR;
  const uint8_t *LED_VAL;

  const uint8_t *DIGIT_ADDR;
};

struct VMD_config {

  const uint8_t TOTAL_DIGITS;
  const uint8_t *LED_ADDR;
  const uint8_t *LED_VAL;

  const uint8_t *DIGIT_BITPOS;
  const uint8_t **SEG_ADDR;
};

#endif
