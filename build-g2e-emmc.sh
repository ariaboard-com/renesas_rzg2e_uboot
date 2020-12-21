export ARCH="arm64"
export CORES=`getconf _NPROCESSORS_ONLN`
export CROSS_COMPILE="aarch64-linux-gnu-"
export WORKDIR="$(pwd)"
export PATH="${WORKDIR}/../gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin:$PATH"

if [ x"$1" = x"mrprober" ]; then
   rm -rf build
fi

if [ ! -d build ]; then
    mkdir -p build
fi

make O=build r8a774c0_ek874_emmc_defconfig
make O=build -j2

rm -rf deploy 2>/dev/null || true
mkdir -p deploy
cp -v build/u-boot-elf.srec deploy/

