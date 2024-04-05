# Operating System for Raspberry Pi 4 Model B

This repository holds source code and documentation related to the CS 652
(Real-time Programming) kernel with some modifications, as designed and developed
by Roberto Valenzuela (roemvaar).

<!--
## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

-->

## Design Goals

Small operating system with a "real-world" application.

Start from scratch to get a better understanding of things that you may
take for granted, such as booting, device interaction, memory management,
timing, threading and concurrency.


## Documentation

The documentation for the project is stored within the ``doc/`` subdirectory. 

The official kernel API for the course is stored ([here](https://student.cs.uwaterloo.ca/~cs452/F23/assignments/kernel.html)).\
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

At the lab:

```
$ cd path/to/kernel
$ make
```

Local development:

```
$ cd path/to/kernel
$ make XDEV=/path/to/cross_toolchain
```

Make sure to specify the path to the cross toolchain on your dev machine.


## Usage

<!-- We follow the [Google style guidelines](https://google.github.io/styleguide/cppguide.html). -->

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

<!-- See the course web page for detailed instructions on how to [build and deploy instructions](https://student.cs.uwaterloo.ca/~cs452/F23/). -->

<!-- ## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.


## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc. -->


## Authors

Roberto Valenzuela (roemvaar).


## Acknowledgements

> _We stand on the shoulders of giants._

Here are some useful resources that we have encountered regarding developing a kernel, real time or otherwise.

* [raspberry-pi-os by Sergey Matyukevich](https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson01/rpi-os.html)

* [rpi4-osdev by Adam Greenwood-Byrne](https://www.rpi4os.com/)

* [CS 452/652 - Real-time Programming by University of Waterloo](https://student.cs.uwaterloo.ca/~cs452/F23/)

<!-- - FreeRTOS-Kernel on Github: [Link](https://github.com/FreeRTOS/FreeRTOS-Kernel)
- Linux Kernel Development, Robert Love (3rd ed.) (doi:10.5555/1855096)
- Operating Systems: Three Easy Pieces: [Link](https://pages.cs.wisc.edu/~remzi/OSTEP/)
- AArch64 Instruction quickstart: [Link](https://wiki.cdot.senecacollege.ca/wiki/AArch64_Register_and_Instruction_Quick_Start) -->
 

## License

MIT license.
