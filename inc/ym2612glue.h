#ifndef YM2612_INCLUDE_GLUE
#define YM2612_INCLUDE_GLUE

#ifndef NULL
#define NULL 0
#endif

#include "ym2612hw.h"

#define YM2612_INIT_OK                     0x00
#define YM2612_INIT_ERROR_UNSPECIFIED      0xFF

typedef struct {
  cs : 1, wr : 1, rd : 1,
  a0 : 1, a1 : 1,
  ic : 1;
} ymcontrolbus_t;

static unsigned char* controldir = NULL;
static ymcontrolbus_t* controlbus = NULL;
static unsigned char* databus = NULL;
static unsigned char* datadir = NULL;

unsigned char ym2612_init(unsigned char* controlbus, unsigned char* controldir, unsigned char* databus, unsigned char* datadir);
void ym2612_write(unsigned char reg, unsigned char part, unsigned char dat);
unsigned char ym2612_read(unsigned char reg, unsigned char part);

#endif