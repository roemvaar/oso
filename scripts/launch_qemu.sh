#!/bin/sh

qemu-system-aarch64 -M virt -m 2G -kernel src/kernel8.elf
