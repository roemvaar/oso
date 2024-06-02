#!/bin/sh

mkdir -p cov-int
make clean
cov-build --dir cov-int make
tar caf oso.xz cov-int
