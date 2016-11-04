#ifndef NULL
#define NULL 0
#endif

#include "ym2612action.h"
#include "ym2612hw.h"

#define YM2612_INIT_OK                     0x00
#define YM2612_INIT_ERROR_UNSPECIFIED      0xFF

static unsigned char* cmdbus = NULL;
static unsigned char* databus = NULL;
static unsigned char* datadir = NULL;

static unsigned char selreg = 0;

unsigned char ym2612_init(unsigned char* cmdbus, unsigned char* databus, unsigned char* datadir);

void ym2612_write(unsigned char reg, unsigned char part, unsigned char data);
void ym2612_read(unsigned char reg, unsigned char part);
