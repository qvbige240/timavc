#! /bin/bash

libtoolize
aclocal
autoheader
automake --add-missing
autoconf

 ######################## x86 ########################
export FINAL_PATH=/home/zouqing/work/carnet/linux/auto/premake/x86/install
 export GOLBAL_CFLAGS="-I/usr/include -I$FINAL_PATH/include"
 export GOLBAL_CPPFLAGS="-I/usr/include -I$FINAL_PATH/include"
 export GOLBAL_LDFLAGS="-L/usr/lib -L$FINAL_PATH/lib"
 export platform=x86
 # ../configure --prefix=/home/zouqing/work/carnet/linux/auto/timavc/install --enable-zlog


 ######################## nt966x ########################
export INSTALL_PATH=/home/zouqing/work/carnet/linux/auto/premake/nt966x/install
export FINAL_PATH=$INSTALL_PATH

# build environment
export INSTALLDIR=/opt/mipsel-24kec-linux-uclibc/usr
export PATH=$PATH:$INSTALLDIR/bin
export TARGETMACH=mipsel-24kec-linux-uclibc
export BUILDMACH=i686-pc-linux-gnu
export CROSS=mipsel-24kec-linux-uclibc-
export CC=${CROSS}gcc
export LD=${CROSS}ld
export AS=${CROSS}as
export CXX=${CROSS}g++

export GBASE_INCLUDE="/opt/mipsel-24kec-linux-uclibc/usr/mipsel-24kec-linux-uclibc/sysroot/usr/include"
export GBASE_LIB="/opt/mipsel-24kec-linux-uclibc/usr/mipsel-24kec-linux-uclibc/sysroot/lib"
export GOLBAL_CFLAGS="-I${GBASE_INCLUDE} -I${FINAL_PATH}/include"
export GOLBAL_CPPFLAGS="-I${GBASE_INCLUDE} -I${FINAL_PATH}/include"
export GOLBAL_LDFLAGS="-L${GBASE_LIB} -L${FINAL_PATH}/lib"
export platform=nt966x
# ../configure --prefix=/home/zouqing/work/carnet/linux/auto/timavc/install --host=$TARGETMACH --enable-zlog
