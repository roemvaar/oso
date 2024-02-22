# Kernel Init

## Booting the Kernel

The Raspberry Pi 4 startup sequence is:

1. The device is powered on
<!-- 2. The GPU starts up and reads the config.txt file from the boot partition. This file contains some configuration parameters that the GPU uses to further adjust the startup sequence. [CHECK THIS ON THE MANUAL] -->
3. `kernel8.img` is loaded into memory and executed
<!-- TODO: check the modifications I did to config.txt
To be able to run our simple OS, the `config.txt.` file should be th following: -->
4. `boot.S` is the first code to run, it makes sure that the code is running in the main
processor, hang all other cores, i.e., this is a single core OS, and make sure that we are
running on execution level 1 (hypervisor). After the set up and checks are completed,
`boot.S` jumps to the `kmain` function.
5. `kmain` do some initialization and then starts the scheduler 

## References

* https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson01/rpi-os.html
