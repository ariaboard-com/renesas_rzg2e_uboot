#!/bin/sh

mkdir -p build

export CROSS_COMPILE="aarch64-linux-gnu-"
export ARCH="arm64"

if [ ! -f "build/.config" ]; then
    make O=build r8a774c0_ek874_defconfig
fi

make O=build -j2
