#include <Arduino.h> //for "byte"

byte DefaultFont(char asciiChar) {

  // case conversion
  asciiChar =
      (asciiChar >= 'a' && asciiChar <= 'z') ? asciiChar - 32 : asciiChar;

  switch (asciiChar) {

  case ' ':
    return 0b0000000;
  case '!':
    return 0b0001110;
  case '"':
    return 0b0100010;
  case '#':
    return 0b1111110;
  case '$':
    return 0b1101101;
  case '%':
    return 0b0101101;
  case '\'':
    return 0b0100000;
  case '(':
    return 0b0110000;
  case ')':
    return 0b0000110;
  case '*':
    return 0b1100011;
  case ',':
    return 0b0010000;
  case '-':
    return 0b1000000;
  case '.':
    return 0b0001000;
  case '/':
    return 0b1010010;
  case '0':
    return 0b0111111;
  case '1':
    return 0b0000110;
  case '2':
    return 0b1011011;
  case '3':
    return 0b1001111;
  case '4':
    return 0b1100110;
  case '5':
    return 0b1101101;
  case '6':
    return 0b1111101;
  case '7':
    return 0b0000111;
  case '8':
    return 0b1111111;
  case '9':
    return 0b1101111;
  case ':':
    return 0b0001001;
  case ';':
    return 0b0000101;
  case '<':
    return 0b1000110;
  case '=':
    return 0b1001000;
  case '>':
    return 0b1110000;
  case '?':
    return 0b1010011;
  case '@':
    return 0b1011111;
  case 'A':
    return 0b1110111;
  case 'B':
    return 0b1111100;
  case 'C':
    return 0b0111001;
  case 'D':
    return 0b1011110;
  case 'E':
    return 0b1111001;
  case 'F':
    return 0b1110001;
  case 'G':
    return 0b0111101;
  case 'H':
    return 0b1110110;
  case 'I':
    return 0b0110000;
  case 'J':
    return 0b0001110;
  case 'K':
    return 0b1110101;
  case 'L':
    return 0b0111000;
  case 'M':
    return 0b1010101;
  case 'N':
    return 0b1010100;
  case 'O':
    return 0b1011100;
  case 'P':
    return 0b1110011;
  case 'Q':
    return 0b1100111;
  case 'R':
    return 0b1010000;
  case 'S':
    return 0b1101101;
  case 'T':
    return 0b1111000;
  case 'U':
    return 0b0111110;
  case 'V':
    return 0b0101010;
  case 'W':
    return 0b1101010;
  case 'X':
    return 0b0010100;
  case 'Y':
    return 0b1101110;
  case 'Z':
    return 0b1011011;
  case '[':
    return 0b0111001;
  case '\\':
    return 0b1100100;
  case ']':
    return 0b0001111;
  case '_':
    return 0b0001000;

  default:
    return 0b0000000;
  }
}
