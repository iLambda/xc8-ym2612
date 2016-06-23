#ifndef NULL
#define NULL 0
#endif

static unsigned char* cmdbus = NULL;
static unsigned char* databus = NULL;
static unsigned char* datadir = NULL;

static unsigned char selreg = 0;

void glue2612_set1reg(unsigned char reg, unsigned char val);
void glue2612_set2reg(unsigned char reg, unsigned char val);

void glue2612_get1reg(unsigned char reg, unsigned char reg);
void glue2612_get2reg(unsigned char reg, unsigned char reg);

void glue2612_getreg(unsigned char reg, unsigned char val, unsigned char part);
