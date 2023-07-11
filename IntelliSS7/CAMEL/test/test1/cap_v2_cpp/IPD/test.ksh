#!/bin/ksh
. ~pmandal/.profile
curDir=$(pwd)
ITS_ROOT=/export/home/pmandal/cvsroot/Accelero5.0
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ITS_ROOT/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$curDir
export LD_LIBRARY_PATH
#gdb ./test
./test
