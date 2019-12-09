#! /bin/bash

libtoolize
aclocal
autoconf
autoheader
automake --add-missing

export FINAL_PATH=/home/zouqing/work/carnet/linux/auto/premake/x86/install
 export GOLBAL_CFLAGS="-I/usr/include -I$FINAL_PATH/include"
 export GOLBAL_CPPFLAGS="-I/usr/include -I$FINAL_PATH/include"
 export GOLBAL_LDFLAGS="-L/usr/lib -L$FINAL_PATH/lib"
 export platform=x86
 