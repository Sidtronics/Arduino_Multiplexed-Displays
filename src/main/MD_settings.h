#ifndef MD_SETTINGS_H
#define MD_SETTINGS_H

// Library constants:
#define MD_DISPLAY_RAM_SIZE 14
#define MD_STRING_BUFFER_SIZE 25

/*-----------------------------*/
// Commands with corresponding flags:

/*******************************/
// Command 1: Mode setting
#define MD_CMD_MODE_SETTING 0x00
/*******************************/

/*******************************/
// Command 2: Data setting
#define MD_CMD_DATA_SETTING 0x40

// Flag: Operation type
#define MD_FLG_NORMAL_OP 0x00
#define MD_FLG_TEST_OP 0x08

// Flag: Address setting
#define MD_FLG_INCREMENTAL_ADDR 0x00
#define MD_FLG_FIXED_ADDR 0x04

// Flag: Read/Write
#define MD_FLG_WRITE 0x00
#define MD_FLG_READ 0x02
/*******************************/

/*******************************/
// Command 3: Address setting
#define MD_CMD_ADDR_SETTING 0xC0
/*******************************/

/*******************************/
// Command 4: Display Control
#define MD_CMD_DISPLAY_CONTROL 0x80

// Flag: Display state
#define MD_FLG_ON 0x08
#define MD_FLG_OFF 0x00

// Flag: Display brightness
#define MD_FLG_LVL0 0x00
#define MD_FLG_LVL1 0x01
#define MD_FLG_LVL2 0x02
#define MD_FLG_LVL3 0x03
#define MD_FLG_LVL4 0x04
#define MD_FLG_LVL5 0x05
#define MD_FLG_LVL6 0x06
#define MD_FLG_LVL7 0x07
/*******************************/

#endif
