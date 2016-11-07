#include "ym2612.h"

int main(void) {

  ym2612_write(0x22, YM2612_PART_1, 0x00); // LFO off
  ym2612_write(0x27, YM2612_PART_1, 0x00); // Note off (channel 0)
  ym2612_write(0x28, YM2612_PART_1, 0x01); // Note off (channel 1)
  ym2612_write(0x28, YM2612_PART_1, 0x02); // Note off (channel 2)
  ym2612_write(0x28, YM2612_PART_1, 0x04); // Note off (channel 3)
  ym2612_write(0x28, YM2612_PART_1, 0x05); // Note off (channel 4)
  ym2612_write(0x28, YM2612_PART_1, 0x06); // Note off (channel 5)
  ym2612_write(0x2B, YM2612_PART_1, 0x00); // DAC off
  ym2612_write(0x30, YM2612_PART_1, 0x71); //
  ym2612_write(0x34, YM2612_PART_1, 0x0D); //
  ym2612_write(0x38, YM2612_PART_1, 0x33); //
  ym2612_write(0x3C, YM2612_PART_1, 0x01); // DT1/MUL
  ym2612_write(0x40, YM2612_PART_1, 0x23); //
  ym2612_write(0x44, YM2612_PART_1, 0x2D); //
  ym2612_write(0x48, YM2612_PART_1, 0x26); //
  ym2612_write(0x4C, YM2612_PART_1, 0x00); // Total level
  ym2612_write(0x50, YM2612_PART_1, 0x5F); //
  ym2612_write(0x54, YM2612_PART_1, 0x99); //
  ym2612_write(0x58, YM2612_PART_1, 0x5F); //
  ym2612_write(0x5C, YM2612_PART_1, 0x94); // RS/AR
  ym2612_write(0x60, YM2612_PART_1, 0x05); //
  ym2612_write(0x64, YM2612_PART_1, 0x05); //
  ym2612_write(0x68, YM2612_PART_1, 0x05); //
  ym2612_write(0x6C, YM2612_PART_1, 0x07); // AM/D1R
  ym2612_write(0x70, YM2612_PART_1, 0x02); //
  ym2612_write(0x74, YM2612_PART_1, 0x02); //
  ym2612_write(0x78, YM2612_PART_1, 0x02); //
  ym2612_write(0x7C, YM2612_PART_1, 0x02); // D2R
  ym2612_write(0x80, YM2612_PART_1, 0x11); //
  ym2612_write(0x84, YM2612_PART_1, 0x11); //
  ym2612_write(0x88, YM2612_PART_1, 0x11); //
  ym2612_write(0x8C, YM2612_PART_1, 0xA6); // D1L/RR
  ym2612_write(0x90, YM2612_PART_1, 0x00); //
  ym2612_write(0x94, YM2612_PART_1, 0x00); //
  ym2612_write(0x98, YM2612_PART_1, 0x00); //
  ym2612_write(0x9C, YM2612_PART_1, 0x00); // Proprietary
  ym2612_write(0xB0, YM2612_PART_1, 0x32); // Feedback/algorithm
  ym2612_write(0xB4, YM2612_PART_1, 0xC0); // Both speakers on
  ym2612_write(0x28, YM2612_PART_1, 0x00); // Key off
  ym2612_write(0xA4, YM2612_PART_1, 0x22);	//
  ym2612_write(0xA0, YM2612_PART_1, 0x69); // Set frequency

  for(;;) {
		delay_ms(1000);
		ym2612_write(0x28, YM2612_PART_1, 0xF0); // Key on
		delay_ms(1000);
		ym2612_write(0x28, YM2612_PART_1, 0x00); // Key off
	}

  return 0;
}
