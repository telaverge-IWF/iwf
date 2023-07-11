#!/bin/ksh
rel=PR5
arg='DEBUG_BUILD=yes'
prog="${0##*/}"
prog=$(echo $prog | cut -d'.' -f1)
if [[ $rel != "" ]]; then
  prog=$(basename `pwd`)-${rel}%${prog}
else
  prog=$(basename `pwd`)%${prog}
fi
tmp=$(pwd)/tmp
errorFile=$tmp/${prog}$1.err
logFile=$tmp/${prog}$1.log
if ! [[ -d $tmp ]]; then
mkdir -p $tmp
fi

make $1 2> $errorFile | tee $logFile
