#ifndef NULL
#define NULL 0
#endif

#include "ym2612action.h"
#include "ym2612hw.h"

#define YM2612_INIT_OK                     0x00
#define YM2612_INIT_ERROR_UNSPECIFIED      0xFF

static unsigned char* controldir = NULL;
static ymcontrolbus_t* controlbus = NULL;
static unsigned char* databus = NULL;
static unsigned char* datadir = NULL;

typedef struct {
  cs : 1, wr : 1, rd : 1
  a0 : 1, a1 : 1,
  ic : 1,
  unsigned: 2
} ymcontrolbus_t;

unsigned char ym2612_init(unsigned char* controlbus, unsigned char* controldir, unsigned char* databus, unsigned char* datadir);
void ym2612_write(unsigned char reg, unsigned char part, unsigned char data);
unsigned char ym2612_read(unsigned char reg, unsigned char part);
