# ym2612-glue

## description

This C library for PIC18F allows you to control a [Yamaha YM2612](https://en.wikipedia.org/wiki/Yamaha_YM2612) in order to make sound.

## how does it work ?

The chip has internal registers that describe how the sound is generated. A list of different registers can be found on the [SEGA2.DOC file](http://www.smspower.org/maxim/Documents/YM2612#reg22).

## api



## technical data

![Pinout of YM2612](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/Yamaha_YM2612_pinout.svg/300px-Yamaha_YM2612_pinout.svg.png)

| # |  Pin | Function |
|---|---|---|
| 1/12  | GND  |  Ground |
| 2-9  | DO-D7 | 8-bit bidirectional data bus  |
| 10  |  NC | Not connected  |
| 11  | /IC  | System reset (active low)  |
| 13  | /IRQ  | Maskable interrupt (active low) |
| 14  | /CS  | Chip select (active low)  |
| 15  | /WR  | Write mode on data bus (active low) |
| 16  | /RD  | Read mode on data bus (active low) |
| 17  | A0  | Read/write enable |
| 18  | A1  | Part 1/2 select  |
| 19  | A.GND |  Analog ground terminal for internal DAC |
| 20/21  | MOL, MOR  | Analog sound outputs, left and right  |
| 22  | A.Vcc  | Analog VCC terminal for DAC |
| 23  | Vcc  | +5V power terminal |
| 24  | CLK | Master clock ||

## sources

* [Wikipedia, *Yamaha YM2612*](https://en.wikipedia.org/wiki/Yamaha_YM2612)
* [Maxim's world of stuff, *SEGA2.DOC transcription*](http://www.smspower.org/maxim/Documents/YM2612#reg22)
