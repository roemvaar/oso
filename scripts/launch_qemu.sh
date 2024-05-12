#!/bin/sh

qemu-system-aarch64 -machine virt -cpu cortex-a72 -kernel build/kernel8.elf -nographic
