#ifndef NULL
#define NULL 0
#endif

#include "ym2612action.h"

static unsigned char* cmdbus = NULL;
static unsigned char* databus = NULL;
static unsigned char* datadir = NULL;

static unsigned char selreg = 0;

void ym2612_init(unsigned char* cmdbus, unsigned char* databus, unsigned char* datadir);
void ym2612_do(ymaction_t action);
