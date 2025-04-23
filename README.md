# arduino-promicro-volume

A USB volume and mute button for computers, done by acting like a keyboard.


![v0.1](https://raw.githubusercontent.com/scarfboy/arduino-promicro-usb-volume/main/v0.1.JPG)

Version 0.1, for wiring reference.


## Hardware

* Arduino Pro Micro, which is basically a mini Leonardo, and based on the already-USB-capable ATmega32U4 which makes makes life a lot simpler when doing USB HID device stuff

* HW-040 rotary encoder.
  * Any encoder should do, really.
  * The ability to press it for mute is nice. I personally use that more than the turning.
  * You may wish to find an encoder that _does_ have threading to fasten it. This one doesn't, so you need to rest its board on something - on something that won't break over time due to hitting it for mute (heat glue is simple and works pretty well)

* A heigtened variant of [this case](https://www.thingiverse.com/thing:2389583) to include both boards, and slightly widened to also allow for the slightly wider PCB of this particular encoder board

* USB cable - stress-relieved by that case

## Software

* the code in `volume.ino`

* Third-party Arduino libraries 
  * HID-Project
  * BasicEncoder
