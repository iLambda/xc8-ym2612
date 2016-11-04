#include "ym2612glue.h"

void ym2612_init(unsigned char* cb, unsigned char* db, unsigned char* dd) {
  // Save buses
  cmdbus = cb;
  databus = db;
  datadir = dd;

  // Set chip in high impedance mode
  datadir = 0x00;
  cmdbus = 0x08;
  databus = 0x00;

  // Everything is ok
  if (1) {
    return YM2612_INIT_OK;
  }

  // An unspecified error
  return YM2612_INIT_ERROR_UNSPECIFIED;
}

void ym2612_write(unsigned char reg, unsigned char part, unsigned char data) {
  /*
  while(busy) {
    asm nop;
  }
  */
}

void ym2612_read(unsigned char reg, unsigned char part) {

}
