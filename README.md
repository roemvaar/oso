# RTOS for Raspberry Pi 4 Model B

University of Waterloo CS652 - Real-Time Programming 
Project (Kernel) with some personal additions

## Design Goal

Small operating system with a "real-world" application.

Start from scratch to get a better understanding of things that you may
take for granted, such as booting, device interaction, memory management,
timing, threading and concurrency.

## Equipment

* Raspberry Pi 4 (RPi4) Model B (with power supply)
* MicroSD Card (and an adapter to write to it)
* USB to TTL serial adapter
* Dev machine (to develop the firmware)

## Software Prerequisites

The RPi4 boot mechanism is closed source, therefore, we need to install
Raspbian OS. See the official [documentation](https://www.raspberrypi.com/software/)
for detailed instructions. After you make sure that your RPi4 is booting
Raspbian correctly, we are going to be able to boot our own code (explained
in the next section).

## Development

To build and test the kernel follow this instructions:

1. Build code

```
$ make
```

2. Copy the generated `kernel8.img` file to the `boot` partition of the RPi4 flash card.
Make sure that you leave all other files in the boot partition untouched.

3. Connect the USB-to-TTL serial cable.

```
$ sudo picocom -b 115200 /dev/ttyUSB0
```

4. Power on the Raspberry Pi 4.

5. On the terminal, you should be able to see the OS booting.


## Acknowledgements

* [raspberry-pi-os by Sergey Matyukevich](https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson01/rpi-os.html)

* [rpi4-osdev by Adam Greenwood-Byrne](https://www.rpi4os.com/)
