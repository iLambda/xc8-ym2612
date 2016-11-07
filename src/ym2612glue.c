#include "ym2612glue.h"

void ym2612_init(unsigned char* cb, unsigned char* db, unsigned char* db, unsigned char* db) {
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

void ym2612_write(unsigned char reg, unsigned char part, unsigned char dat) {
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
  *databus = dat;
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

unsigned char ym2612_read(unsigned char reg, unsigned char part) {
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
  *databus = dat;
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
  unsigned char dat;
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
