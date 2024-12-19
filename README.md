# OSo

OSo ("bear" in Spanish) is a microkernel for embedded systems as designed and developed
by Roberto Valenzuela (roemvaar). It currently supports Raspberry Pi 4 Model B.


## Build Status

**master:**  <a href="https://scan.coverity.com/projects/roemvaar-oso">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/30303/badge.svg"/>
</a>


## Design Goals

Small operating system with for "real-world" applications.

Start from scratch to get a better understanding of things that you may
take for granted, such as booting, device interaction, memory management,
timing, threading and concurrency.


## Documentation

The documentation for the project is in the [Wiki](https://github.com/roemvaar/oso/wiki) page. 

The assignment-related files are stored on the course site ([here](https://student.cs.uwaterloo.ca/~cs452/F23/)).


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


## Build

First, install the cross toolchain, instructions [here](https://github.com/roemvaar/oso/wiki#toolchain).

```
$ make X_DIR=/path/to/cross_toolchain
```

Make sure to specify the path to the cross toolchain on your dev machine.


## Usage

The `make` command will produce `kernel8.img`, which is a memory image of our kernel. This binary is the
one that needs to be deployed to the RPi4 and run. The steps consists of flashing the image into the SD
card, then inserting it into the RPi4, then powering the board, and the kernel should start booting and
running the user space "applications".

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


## Debugging

```
$ make debug
```

The `debug` target produces the `objdump.txt` and `readelf.txt` that help to debug the kernel.


## Authors

Roberto Valenzuela (roemvaar).


## Acknowledgements

> _We stand on the shoulders of giants._

Here are some useful resources that we have encountered regarding developing a kernel, real time or otherwise.

* [raspberry-pi-os by Sergey Matyukevich](https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson01/rpi-os.html)

* [rpi4-osdev by Adam Greenwood-Byrne](https://www.rpi4os.com/)

* [CS 452/652 - Real-time Programming by University of Waterloo](https://student.cs.uwaterloo.ca/~cs452/F23/) 


## License

[MIT License](https://github.com/roemvaar/oso/blob/main/LICENSE).
