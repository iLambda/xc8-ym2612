#include "ym2612.h"

uint8_t ym2612_init(uint8_t* cb, uint8_t* cd, uint8_t* db, uint8_t* dd) {
  // Save buses
  controlbus = (ymcontrolbus_t*)(void*)cb;
  controldir = cd;
  databus = db;
  datadir = dd;

  // Direction setup
  *controldir = 0x00;
  *datadir = 0x00;

  // Bus setup
  controlbus->ic = 1;
  controlbus->cs = 1;
  controlbus->wr = 1;
  controlbus->rd = 1;
  controlbus->a0 = 0;
  controlbus->a1 = 0;

  // Activate PWM for YM2612 clock
  PWM1_Init(8000);
  PWM1_Set_Duty(0x7F);
  PWM1_Start();

  // Reset
  controlbus->ic = 0;
  delay_ms(10);
  controlbus->ic = 1;
  delay_ms(10);

  // Everything is ok
  if (1) {
    return YM2612_INIT_OK;
  }

  // An unspecified error
  return YM2612_INIT_ERROR_UNSPECIFIED;
}

void ym2612_write(uint8_t reg, uint8_t part, uint8_t dat) {
  // set data as output
  *datadir = 0x00;

  // set part
  controlbus->a1 = part & YM2612_PART_2;

  // select reg mode
  controlbus->wr = 0;
  controlbus->rd = 1;
  controlbus->a0 = 0;
  // cs low
  controlbus->cs = 0;
  // set data
  *databus = reg;
  // wait
  delay_us(1);
  // write data
  controlbus->wr = 0;
  controlbus->rd = 1;
  // wait
  delay_us(5);
  // end write data
  controlbus->wr = 1;
  // wait
  delay_us(5);
  // cs high
  controlbus->cs = 1;

  // a0 high (write reg)
  controlbus->a0 = 1;
  // cs low
  controlbus->cs = 0;
  // set data
  *databus = dat;
  // wait
  delay_us(1);
  // write data
  controlbus->wr = 0;
  // wait
  delay_us(5);
  // write data
  controlbus->wr = 1;
  // wait
  delay_us(5);
  // cs high
  controlbus->cs = 1;

  // wait
  delay_us(1);
}

uint8_t ym2612_read(uint8_t reg, uint8_t part) {
  uint8_t dat;

  // set data as input
  *datadir = 0x00;

  // set part
  controlbus->a1 = part & YM2612_PART_2;

  // select reg mode
  controlbus->wr = 0;
  controlbus->rd = 1;
  controlbus->a0 = 0;
  // cs low
  controlbus->cs = 0;
  // set data
  *databus = reg;
  // wait
  delay_us(1);
  // write data
  controlbus->wr = 0;
  controlbus->rd = 1;
  // wait
  delay_us(5);
  // end write data
  controlbus->wr = 1;
  // wait
  delay_us(5);
  // cs high
  controlbus->cs = 1;

  // set data Direction
  *datadir = 0xFF;

  // a0 high (read reg)
  controlbus->wr = 1;
  controlbus->rd = 0;
  controlbus->a0 = 1;
  // cs low
  controlbus->cs = 0;
  // wait
  delay_us(5);
  // get data
  dat = *databus;
  // wait
  delay_us(2);
  // set data Direction
  *datadir = 0x00;
  // cs high
  controlbus->cs = 1;
  // wait
  delay_us(1);

  // return
  return dat;
}

uint8_t ym2612_getLFO(){
  return ym2612_read(YM2612_REG_LFO, YM2612_PART_1);
}

uint8_t ym2612_getChannel36(){
  return ym2612_read(YM2612_REG_CH36MODE, YM2612_PART_1);
}

uint8_t ym2612_getDAC(){
  return ym2612_read(YM2612_REG_DACENBL, YM2612_PART_1);
}

uint8_t ym2612_getDACData(){
  return ym2612_read(YM2612_REG_DACDATA, YM2612_PART_1);
}

uint8_t ym2612_getOperatorFreq(uint8_t channel, uint8_t op){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_DETMUL + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

void ym2612_getEnvelope(uint8_t channel, uint8_t op, ymenvelope_t* envelope){
  // channel/op contribution to address
  uint8_t daddr, part, attack, decay, sustain, release;
  daddr = (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // getting all registers
  attack = ym2612_read(daddr + YM2612_REG_CH1OP1_RATEH, part);
  decay = ym2612_read(daddr + YM2612_REG_CH1OP1_RATEMH, part);
  sustain = ym2612_read(daddr + YM2612_REG_CH1OP1_RATEML, part);
  release = ym2612_read(daddr + YM2612_REG_CH1OP1_RATEL, part);
  // the total level
  envelope->tl = YM2612_TL_MAX - (envelope->tl & YM2612_TL_MAX);
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

uint8_t ym2612_getEnvelopeTotalLevel(uint8_t channel, uint8_t op){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_TL + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return YM2612_TL_MAX - (ym2612_read(addr, part) & YM2612_TL_MAX);
}

uint8_t ym2612_getEnvelopeAttack(uint8_t channel, uint8_t op){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEH + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

uint8_t ym2612_getEnvelopeDecay(uint8_t channel, uint8_t op){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEMH + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

uint8_t ym2612_getEnvelopeSustain(uint8_t channel, uint8_t op){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEML + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

uint8_t ym2612_getEnvelopeRelease(uint8_t channel, uint8_t op){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEL + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

uint16_t ym2612_getFrequency(uint8_t channel) {
  uint8_t addrlow, part, datlow, dathigh;
  addrlow = YM2612_REG_CH1_FREQL + (channel % 3);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;

  // read high THEN low
  dathigh = ym2612_read(addrlow + 0x04, part);
  datlow = ym2612_read(addrlow, part);
  // return integer
  return (uint16_t)(datahigh << 8) | dathigh;
}

uint16_t ym2612_getFrequency36(uint8_t channel, uint8_t op){
  uint8_t addrlow, part, datlow, dathigh;
  // check if channel is correct
  if (channel != YM2612_CHANNEL_3 && channel != YM2612_CHANNEL_6) { return 0; }

  // compute addr
  addrlow = op != YM2612_OPERATOR_1 ? YM2612_REG_CH3OP2_FREQL - 1 + op : YM2612_REG_CH3OP1_FREQL;
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // read high THEN low
  dathigh = ym2612_read(addrlow + 0x04, part);
  datlow = ym2612_read(addrlow, part);
  // return integer
  return (uint16_t)(datahigh << 8) | dathigh;
}

uint8_t ym2612_getAlgorithm(uint8_t channel){
  uint8_t addr, part;
  addr = YM2612_REG_CH1_ALGO + (channel % 3);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}

uint8_t ym2612_getStereoSensivity(uint8_t channel){
  uint8_t addr, part;
  addr = YM2612_REG_CH1_STEREOSENSIVITY + (channel % 3);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  return ym2612_read(addr, part);
}


void ym2612_setLFO(uint8_t enable, uint8_t frequency){
  ym2612_write(YM2612_REG_LFO, YM2612_PART_1, (enable & YM2612_LFO_ON) | (frequency & 0x07));
}

void ym2612_setChannel36(uint8_t enable){
  ym2612_write(YM2612_REG_CH36MODE, YM2612_PART_1, enable & 0xC0);
}

void ym2612_setKeyOnOff(uint8_t channel, uint8_t opmask){
  channel = channel <= 3 ? channel : channel + 1;
  ym2612_write(YM2612_REG_KEYONOFF, YM2612_PART_1, ((opmask & 0x0F) << 4) | (channel & 0x07));
}

void ym2612_setDAC(uint8_t enable){
  ym2612_write(YM2612_REG_DACENBL, YM2612_PART_1, enable ? YM2612_DAC_ON : YM2612_DAC_ON);
}

void ym2612_setDACData(uint8_t dat){
  ym2612_write(YM2612_REG_DACDATA, YM2612_PART_1, dat);
}

void ym2612_setOperatorFreq(uint8_t channel, uint8_t op, uint8_t freq){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_DETMUL + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, freq & 0x7F);
}

void ym2612_setEnvelope(uint8_t channel, uint8_t op, ymenvelope_t envelope){
  uint8_t daddr, part;
  daddr = (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // TODO : envelope.tl must be computed in binary (faster?)
  ym2612_write(daddr + YM2612_REG_CH1OP1_TL, part, YM2612_TL_MAX - (envelope.tl & YM2612_TL_MAX));
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEH, part, ((envelope.rs & 0x03) << 6) | (envelope.ar & 0x1F));
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEMH, part, (envelope.am & YM2612_AM_ON) | (envelope.d1r & 0x1F));
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEML, part, envelope.d2r & 0x1F);
  ym2612_write(daddr + YM2612_REG_CH1OP1_RATEL, part, (envelope.rr & 0x1F) | ((envelope.d1l & 0x1F) << 4));
}

void ym2612_setEnvelopeTotalLevel(uint8_t channel, uint8_t op, uint8_t level){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_TL + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // TODO : envelope.tl must be computed in binary (faster?)
  ym2612_write(addr, part, YM2612_TL_MAX - (level & YM2612_TL_MAX));
}

void ym2612_setEnvelopeAttack(uint8_t channel, uint8_t op, uint8_t ratescaling, uint8_t attackrate){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEH + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, ((ratescaling & 0x03) << 6) | (attackrate & 0x1F));
}

void ym2612_setEnvelopeDecay(uint8_t channel, uint8_t op, uint8_t am, uint8_t decayrate1){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEMH + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, (am & YM2612_AM_ON) | (decayrate1 & 0x1F));
}

void ym2612_setEnvelopeSustain(uint8_t channel, uint8_t op, uint8_t decayrate2){
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEML + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, decayrate2 & 0x1F);
}

void ym2612_setEnvelopeRelease(uint8_t channel, uint8_t op, uint8_t secondaryamplitude, uint8_t releaserate) {
  uint8_t addr, part;
  addr = YM2612_REG_CH1OP1_RATEL + (channel % 3) + (op * 4);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(addr, part, (releaserate & 0x1F) | ((secondaryamplitude & 0x1F) << 4));
}

void ym2612_setFrequency(uint8_t channel, uint16_t frequency){
  //TODO : how does frequency work?

  uint8_t addrlow, part;
  addrlow = YM2612_REG_CH1_FREQL + (channel % 3);
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  // write high THEN low
  ym2612_write(addrlow + 0x04, part, (uint8_t)(frequency & 0xFF));
  ym2612_write(addrlow, part, (uint8_t)((frequency >> 8) & 0x3F));
}

void ym2612_setFrequency36(uint8_t channel, uint8_t op, uint16_t frequency){
    uint8_t addrlow, part;

    //TODO : how does frequency work?

    // check if channel is correct
    if (channel != YM2612_CHANNEL_3 && channel != YM2612_CHANNEL_6) { return; }
    // compute addr
    addrlow = op != YM2612_OPERATOR_1 ? YM2612_REG_CH3OP2_FREQL - 1 + op : YM2612_REG_CH3OP1_FREQL;
    part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
    // write high THEN low
    ym2612_write(addrlow + 0x04, part, (uint8_t)(frequency & 0xFF));
    ym2612_write(addrlow, part, (uint8_t)((frequency >> 8) & 0x3F));
}

void ym2612_setAlgorithm(uint8_t channel, uint8_t algorithm, uint8_t feedback){
  uint8_t part;
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(YM2612_REG_CH1_ALGO + (channel % 3), part, (algorithm & 0x07) | ((feedback & 0x07) << 3));
}

void ym2612_setStereoSensivity(uint8_t channel, uint8_t stereosensivity){
  uint8_t part;
  part = channel < 3 ? YM2612_PART_1 : YM2612_PART_2;
  ym2612_write(YM2612_REG_CH1_STEREOSENSIVITY + (channel % 3), part, stereosensivity & 0xFB);
}
