# USB temperature & switch
![build](https://github.com/pilotak/usb-temp-switch/workflows/build/badge.svg)

ATtiny85 based USB temperature sensor & humidity (DHT22) and low side switch with serial control

# Install

## Version 1
You need an AVR programmer (ICSP), for how to make one please follow version 2 below (skip the "Burn bootloader")

Upload directly via PlatformIO
```sh
pio run -t upload -e usb_temp_switch_v1
```
or use compiled/downloaded FW with `AVRDUDE` _(don't forget to change the serial port number & fw path)_
```sh
avrdude -v -p attiny85 -c arduino -b 19200 -P COM1 -e -D -U flash:w:firmware.hex:i
```

## Version 2
This HW revision uses an Optiboot bootloader which enables you to upload upgrades via USB.
- install Arduino IDE
- install (ATTinyCore)[https://github.com/SpenceKonde/ATTinyCore]
- follow (this tutorial)[https://create.arduino.cc/projecthub/Oniichan_is_ded/learn-how-to-program-attiny85-and-attiny13a-167359] in order to make your Arduino UNO as an AVR programmer
- connect the ATtiny85 to your programmer from above
- "Burn bootloader" through Arduino IDE

You can now upload directly via PlatformIO
```sh
pio run -t upload -e usb_temp_switch_v2
```
or use compiled/downloaded FW with `AVRDUDE` _(don't forget to change the serial port number & fw path)_
```sh
avrdude -v -p attiny85 -c arduino -b 19200 -P COM1 -e -D -U flash:w:firmware.hex:i
```

# Usage
Open serial port with baud 9600, 8N1. All messages sent/recevied have a newline delimiter (`\n`)

## Switch
- to turn ON the switch send **`d=1`**
- to turn OFF the switch send **`d=0`**

You will always get a confirmation: same massage you sent

## Temperature
Once per set interval you will get a temperature with one decimal place ie.: **`t=22.1`**

## Humidity
Once per set interval you will get a humidity with one decimal place ie.: **`h=50.3`**
