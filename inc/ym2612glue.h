#ifndef NULL
#define NULL 0
#endif

static unsigned char* cmdbus = NULL;
static unsigned char* databus = NULL;
static unsigned char* datadir = NULL;

static unsigned char selreg = 0;

void ym2612_init(unsigned char* cmdbus, unsigned char* databus, unsigned char* datadir);


void ym2612_select(unsigned char addr, unsigned char part);
void ym2612_write(unsigned char addr, unsigned char part);
unsigned char ym2612_read(unsigned char addr, unsigned char part);

unsigned char ym2612_getreg(unsigned char addr, unsigned char part);
void ym2612_setreg(unsigned char addr, unsigned char regval, unsigned char part);
