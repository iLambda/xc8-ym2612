#ifndef NULL
#define NULL 0
#endif

#include "ym2612glue.h"
#include "ym2612envelope.h"

#define YM2612_D1R              0x1F
#define YM2612_D2R              0x1F
#define YM2612_D1L              0xF0
#define YM2612_RR               0x0F

#define YM2612_CHANNEL_1        0x00
#define YM2612_CHANNEL_2        0x01
#define YM2612_CHANNEL_3        0x02
#define YM2612_CHANNEL_4        0x03
#define YM2612_CHANNEL_5        0x04
#define YM2612_CHANNEL_6        0x05

#define YM2612_OPERATOR_1       0x00
#define YM2612_OPERATOR_2       0x01
#define YM2612_OPERATOR_3       0x02
#define YM2612_OPERATOR_4       0x03

#define YM2612_OPERATORMASK_1       0x01
#define YM2612_OPERATORMASK_2       0x02
#define YM2612_OPERATORMASK_3       0x04
#define YM2612_OPERATORMASK_4       0x08
#define YM2612_OPERATORMASK_NONE    0x00
#define YM2612_OPERATORMASK_ALL     YM2612_OPERATOR_1 | \
                                    YM2612_OPERATOR_2 | \
                                    YM2612_OPERATOR_3 | \
                                    YM2612_OPERATOR_4

#define YM2612_LFO_ON           0x08
#define YM2612_LFO_OFF          0x00

#define YM2612_LFO_398          0x00
#define YM2612_LFO_556          0x01
#define YM2612_LFO_602          0x02
#define YM2612_LFO_637          0x03
#define YM2612_LFO_688          0x04
#define YM2612_LFO_963          0x05
#define YM2612_LFO_4810         0x06
#define YM2612_LFO_7220         0x07

#define YM2612_CH36_ON          0x40
#define YM2612_CH36_OFF         0x00

#define YM2612_DAC_ON           0xFF
#define YM2612_DAC_OFF          0x00

#define YM2612_FREQ_DETUNE_1    0x00
#define YM2612_FREQ_DETUNE_1PE  0x10
#define YM2612_FREQ_DETUNE_1P2E 0x20
#define YM2612_FREQ_DETUNE_1P3E 0x30
#define YM2612_FREQ_DETUNE_1ME  0x50
#define YM2612_FREQ_DETUNE_1M2E 0x60
#define YM2612_FREQ_DETUNE_1M3E 0x70

#define YM2612_FREQ_MUL_HALF    0x00
#define YM2612_FREQ_MUL_1       0x01
#define YM2612_FREQ_MUL_2       0x02
#define YM2612_FREQ_MUL_3       0x03
#define YM2612_FREQ_MUL_4       0x04
#define YM2612_FREQ_MUL_5       0x05
#define YM2612_FREQ_MUL_6       0x06
#define YM2612_FREQ_MUL_7       0x07
#define YM2612_FREQ_MUL_8       0x08
#define YM2612_FREQ_MUL_9       0x09
#define YM2612_FREQ_MUL_10      0x0A
#define YM2612_FREQ_MUL_11      0x0B
#define YM2612_FREQ_MUL_12      0x0C
#define YM2612_FREQ_MUL_13      0x0D
#define YM2612_FREQ_MUL_14      0x0E
#define YM2612_FREQ_MUL_15      0x0F

#define YM2612_TL_MIN           0x00
#define YM2612_TL_MAX           0x7F

#define YM2612_RS_MIN           0x00
#define YM2612_RS_8             0x00
#define YM2612_RS_4             0x01
#define YM2612_RS_2             0x02
#define YM2612_RS_1             0x03
#define YM2612_RS_MAX           0x03

#define YM2612_AM_ON            0x80
#define YM2612_AM_OFF           0x00

#define YM2612_OP_FEEDBACK      0b111000
#define YM2612_OP_ALGORITHM     0b111

#define YM2612_STEREO_L         0x80
#define YM2612_STEREO_R         0x40
#define YM2612_STEREO_LR        YM2612_STEREO_L | YM2612_STEREO_R

#define YM2612_AMS_0            0x00
#define YM2612_AMS_14           0x01
#define YM2612_AMS_59           0x02
#define YM2612_AMS_118          0x03

#define YM2612_FMS_0            0x00
#define YM2612_FMS_34           0x01
#define YM2612_FMS_67           0x02
#define YM2612_FMS_100          0x03
#define YM2612_FMS_140          0x04
#define YM2612_FMS_200          0x05
#define YM2612_FMS_400          0x06
#define YM2612_FMS_800          0x07

#define YM2612_FREQ_C
#define YM2612_FREQ_Cs
#define YM2612_FREQ_D

unsigned char ym2612_getLFO();
unsigned char ym2612_getChannel36();
unsigned char ym2612_getDAC();
unsigned char ym2612_getDACData();
unsigned char ym2612_getOperatorFreq(unsigned char channel, unsigned char op);
void ym2612_getEnvelope(unsigned char channel, unsigned char op, ymenvelope_t* envelope);
unsigned char ym2612_getEnvelopeTotalLevel(unsigned char channel, unsigned char op);
unsigned char ym2612_getEnvelopeAttack(unsigned char channel, unsigned char op);
unsigned char ym2612_getEnvelopeDecay(unsigned char channel, unsigned char op);
unsigned char ym2612_getEnvelopeSustain(unsigned char channel, unsigned char op);
unsigned char ym2612_getEnvelopeRelease(unsigned char channel, unsigned char op);
unsigned int ym2612_getFrequency(unsigned char channel, unsigned char octave);
unsigned int ym2612_getFrequency36(unsigned char channel, unsigned char octave);
unsigned char ym2612_getAlgorithm(unsigned char channel);
unsigned char ym2612_getStereoSensivity(unsigned char channel);

void ym2612_setLFO(unsigned char enable, unsigned char frequency);
void ym2612_setChannel36(unsigned char enable);
void ym2612_setKeyOnOff(unsigned char channel, unsigned char operatormask);
void ym2612_setDAC(unsigned char enable);
void ym2612_setDACData(unsigned char dat);
void ym2612_setOperatorFreq(unsigned char channel, unsigned char op, unsigned char freq);
void ym2612_setEnvelope(unsigned char channel, unsigned char op, ymenvelope_t envelope);
void ym2612_setEnvelopeTotalLevel(unsigned char channel, unsigned char op, unsigned char level);
void ym2612_setEnvelopeAttack(unsigned char channel, unsigned char op, unsigned char ratescaling, unsigned char attackrate);
void ym2612_setEnvelopeDecay(unsigned char channel, unsigned char op, unsigned char am, unsigned char decayrate1);
void ym2612_setEnvelopeSustain(unsigned char channel, unsigned char op, unsigned char decayrate2);
void ym2612_setEnvelopeRelease(unsigned char channel, unsigned char op, unsigned char secondaryamplitude, unsigned char releaserate);
void ym2612_setFrequency(unsigned char channel, unsigned int frequency);
void ym2612_setFrequency36(unsigned char channel, unsigned char op, unsigned int frequency);
void ym2612_setAlgorithm(unsigned char channel, unsigned char algorithm, unsigned char feedback);
void ym2612_setStereoSensivity(unsigned char channel, unsigned char stereosensivity);
