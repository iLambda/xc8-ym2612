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

unsigned char ym2612_getOperatorFreq(unsigned char channel, unsigned char op){
  unsigned char addr = YM2612_REG_CH1OP1_DETMUL + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

void ym2612_getEnvelope(unsigned char channel, unsigned char op, ymenvelope_t* envelope){
  // channel/op contribution to address
  unsigned char daddr = (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // getting all registers
  unsigned char attack = ym2612_write(daddr + YM2612_REG_CH1OP1_RATEH, part);
  unsigned char decay = ym2612_write(daddr + YM2612_REG_CH1OP1_RATEMH, part);
  unsigned char sustain = ym2612_write(daddr + YM2612_REG_CH1OP1_RATEML, part);
  unsigned char release = ym2612_write(daddr + YM2612_REG_CH1OP1_RATEL, part);
  // the total level
  envelope->tl = YM2612_TL_MAX - (envelope.tl & YM2612_TL_MAX);
  // fill attack registers
  envelope->rs = attack >> 6;
  envelope->ar = attack & 0x1F;
  // fill decay registers
  envelope->am = decay & YM2612_AM_ON;
  envelope->d1r = decay & 0x1F;
  // fill sustain registers
  envelope->d2r = sustain & 0x1F;
  // fill release
  envelope->d1l = (release >> 4) & 0x0F;
  envelope->rr = release & 0x0F;
}

unsigned char ym2612_getEnvelopeTotalLevel(unsigned char channel, unsigned char op){
  unsigned char addr = YM2612_REG_CH1OP1_TL + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return YM2612_TL_MAX - (ym2612_read(addr, part) & YM2612_TL_MAX);
}

unsigned char ym2612_getEnvelopeAttack(unsigned char channel, unsigned char op){
  unsigned char addr = YM2612_REG_CH1OP1_RATEH + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

unsigned char ym2612_getEnvelopeDecay(unsigned char channel, unsigned char op){
  unsigned char addr = YM2612_REG_CH1OP1_RATEMH + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

unsigned char ym2612_getEnvelopeSustain(unsigned char channel, unsigned char op){
  unsigned char addr = YM2612_REG_CH1OP1_RATEML + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

unsigned char ym2612_getEnvelopeRelease(unsigned char channel, unsigned char op){
  unsigned char addr = YM2612_REG_CH1OP1_RATEL + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

unsigned int ym2612_getFrequency(unsigned char channel, unsigned char octave){}

unsigned int ym2612_getFrequency36(unsigned char channel, unsigned char octave){}

unsigned char ym2612_getAlgorithm(unsigned char channel){
  unsigned char addr = YM2612_REG_CH1_ALGO + (channel % 3);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

unsigned char ym2612_getStereoSensivity(unsigned char channel){
  unsigned char addr = YM2612_REG_CH1_STEREOSENSIVITY + (channel % 3);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}


void ym2612_setLFO(unsigned char enable, unsigned char frequency){
  ym2612_write(YM2612_REG_LFO, YM2612_PART_1, (enable & YM2612_LFO_ON) | (frequency & 0x07));
}

void ym2612_setChannel36(unsigned char enable){
  ym2612_write(YM2612_REG_CH36MODE, YM2612_PART_1, enable & 0xC0);
}

void ym2612_setKeyOnOff(unsigned char channel, unsigned char opmask){
  unsigned char chn = channel <= 3 ? channel : channel + 1;
  ym2612_write(YM2612_REG_KEYONOFF, YM2612_PART_1, ((opmask & 0x0F) << 4) | (chn & 0x07));
}

void ym2612_setDAC(unsigned char enable){
  ym2612_write(YM2612_REG_DACENBL, YM2612_PART_1, enable ? YM2612_DAC_ON : YM2612_DAC_ON);
}

void ym2612_setDACData(unsigned char data){
  ym2612_write(YM2612_REG_DACDATA, YM2612_PART_1, data);
}

void ym2612_setOperatorFreq(unsigned char channel, unsigned char op, unsigned char freq){
  unsigned char addr = YM2612_REG_CH1OP1_DETMUL + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, freq & 0x7F);
}

void ym2612_setEnvelope(unsigned char channel, unsigned char op, ymenvelope_t envelope){
  unsigned char daddr = (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // TODO : envelope.tl must be computed in binary (faster?)
  ym2612_write(daddr + YM2612_REG_CH1OP1_TL, part, YM2612_TL_MAX - (envelope.tl & YM2612_TL_MAX));
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEH, part, ((envelope.rs & 0x03) << 6) | (envelope.ar & 0x1F));
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEMH, part, (envelope.am & YM2612_AM_ON) | (envelope.d1r & 0x1F));
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEML, part, envelope.d2r & 0x1F);
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEL, part, (envelope.rr & 0x1F) | ((envelope.d1l & 0x1F) << 4));
}

void ym2612_setEnvelopeTotalLevel(unsigned char channel, unsigned char op, unsigned char level){
  unsigned char addr = YM2612_REG_CH1OP1_TL + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // TODO : envelope.tl must be computed in binary (faster?)
  ym2612_write(addr, part, YM2612_TL_MAX - (envelope.tl & YM2612_TL_MAX));
}

void ym2612_setEnvelopeAttack(unsigned char channel, unsigned char op, unsigned char ratescaling, unsigned char attackrate){
  unsigned char addr = YM2612_REG_CH1OP1_RATEH + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, ((ratescaling & 0x03) << 6) | (attackrate & 0x1F));
}

void ym2612_setEnvelopeDecay(unsigned char channel, unsigned char op, unsigned char am, unsigned char decayrate1){
  unsigned char addr = YM2612_REG_CH1OP1_RATEMH + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, (am & YM2612_AM_ON) | (decayrate1 & 0x1F));
}

void ym2612_setEnvelopeSustain(unsigned char channel, unsigned char op, unsigned char decayrate2){
  unsigned char addr = YM2612_REG_CH1OP1_RATEML + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, decayrate2 & 0x1F);
}

void ym2612_setEnvelopeRelease(unsigned char channel, unsigned char op, unsigned char secondaryamplitude, unsigned char releaserate) {
  unsigned char addr = YM2612_REG_CH1OP1_RATEL + (channel % 3) + (op * 4);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, (releaserate & 0x1F) | ((secondaryamplitude & 0x1F) << 4));
}

void ym2612_setFrequency(unsigned char channel, unsigned int frequency){
  //TODO : how does frequency work?

  unsigned char addrlow = YM2612_REG_CH1_FREQL + (channel % 3);
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // write high THEN low
  ym2612_write(addrlow + 0x04, part, (unsigned char)(frequency & 0xFF));
  ym2612_write(addrlow, part, (unsigned char)((frequency >> 8) & 0x3F));
}

void ym2612_setFrequency36(unsigned char channel, unsigned char op, unsigned int frequency){
    //TODO : how does frequency work?

    // check if channel is correct
    if (channel != YM2612_CHANNEL_3 && channel != YM2612_CHANNEL_6) { return; }
    // compute addr
    unsigned char addrlow = op != YM2612_OPERATOR_1 ? YM2612_REG_CH3OP2_FREQL - 1 + op : YM2612_REG_CH3OP1_FREQL;
    unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
    // write high THEN low
    ym2612_write(addrlow + 0x04, part, (unsigned char)(frequency & 0xFF));
    ym2612_write(addrlow, part, (unsigned char)((frequency >> 8) & 0x3F));
}

void ym2612_setAlgorithm(unsigned char channel, unsigned char algorithm, unsigned char feedback){
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(YM2612_REG_CH1_ALGO + (channel % 3), part, (algorithm & 0x07) | ((feedback & 0x07) << 3));
}

void ym2612_setStereoSensivity(unsigned char channel, unsigned char stereosensivity){
  unsigned char part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(YM2612_REG_CH1_STEREOSENSIVITY + (channel % 3), part, stereosensivity & 0xFB);
}
