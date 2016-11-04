#include "ym2612.h"
#include "ym2612glue.h"

unsigned char ym2612_getLFO(){
  return ym2612_read(YM2612_REG_LFO, YM2612_PART_1);
}

unsigned char ym2612_getChannel36(){
  return ym2612_read(YM2612_REG_CH36MODE, YM2612_PART_1);
}

unsigned char ym2612_getDAC(){
  return ym2612_read(YM2612_REG_DACENBL, YM2612_PART_1);
}

unsigned char ym2612_getDACData(){
  return ym2612_read(YM2612_REG_DACDATA, YM2612_PART_1);
}

unsigned char ym2612_getOperatorFreq(unsigned char channel, unsigned char operator){}

void ym2612_getEnvelope(unsigned char channel, unsigned char operator, ymenvelope_t* envelope){}

unsigned char ym2612_getEnvelopeTotalLevel(unsigned char channel, unsigned char operator){}

unsigned char ym2612_getEnvelopeAttack(unsigned char channel, unsigned char operator){}

unsigned char ym2612_getEnvelopeDecay(unsigned char channel, unsigned char operator){}

unsigned char ym2612_getEnvelopeSustain(unsigned char channel, unsigned char operator){}

unsigned char ym2612_getEnvelopeRelease(unsigned char channel, unsigned char operator){}

unsigned int ym2612_getFrequency(unsigned char channel, unsigned char octave){}

unsigned int ym2612_getFrequency36(unsigned char channel, unsigned char octave){}

unsigned char ym2612_getAlgorithm(unsigned char channel){}

unsigned char ym2612_getStereoSensivity(unsigned char channel){}


void ym2612_setLFO(unsigned char enable, unsigned char frequency){
  ym2612_write(YM2612_REG_LFO, YM2612_PART_1, (enable & YM2612_LFO_ON) | (frequency & 0x07));
}

void ym2612_setChannel36(unsigned char enable){
  ym2612_write(YM2612_REG_CH36MODE, YM2612_PART_1, enable & 0xC0);
}

void ym2612_setKeyOnOff(unsigned char channel, unsigned char operatormask){
  unsigned char chn = channel <= 3 ? channel - 1 : channel;
  ym2612_write(YM2612_REG_KEYONOFF, YM2612_PART_1, ((operatormask & 0x0F) << 4) | (chn & 0x07));
}

void ym2612_setDAC(unsigned char enable){
  ym2612_write(YM2612_REG_DACENBL, enable ? YM2612_DAC_ON : YM2612_DAC_ON);
}

void ym2612_setDACData(unsigned char data){
  ym2612_write(YM2612_REG_DACDATA, data);
}

void ym2612_setOperatorFreq(unsigned char channel, unsigned char operator, unsigned char freq){}

void ym2612_setEnvelope(unsigned char channel, unsigned char operator, ymenvelope_t envelope){}

void ym2612_setEnvelopeTotalLevel(unsigned char channel, unsigned char operator, unsigned char level){}

void ym2612_setEnvelopeAttack(unsigned char channel, unsigned char operator, unsigned char ratescaling, unsigned char attackrate){}

void ym2612_setEnvelopeDecay(unsigned char channel, unsigned char operator, unsigned char am, unsigned char decayrate1){}

void ym2612_setEnvelopeSustain(unsigned char channel, unsigned char operator, unsigned char decayrate2){}

void ym2612_setEnvelopeRelease(unsigned char channel, unsigned char operator, unsigned char secondaryamplitude, unsigned char releaserate){}

void ym2612_setFrequency(unsigned char channel, unsigned char octave, unsigned char frequency){}

void ym2612_setFrequency36(unsigned char channel, unsigned char octave, unsigned char frequency){}

void ym2612_setAlgorithm(unsigned char channel, unsigned char algorithm, unsigned char feedback){}

void ym2612_setStereoSensivity(unsigned char channel, unsigned char stereosensivity){}
