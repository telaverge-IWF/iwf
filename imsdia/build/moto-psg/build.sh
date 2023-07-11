#!/bin/bash
if [ -z $1 ]
then
   echo
   echo "Invalid platform entry, please follow the below syntax."
   echo "Syntax: ./build.sh platform=[x86/sparc/linux]"
   echo
   exit 1
elif [ $1 == "platform=x86" -o $1 == "platform=sparc" -o $1 == "platform=linux" ]
then
   if [ $1 == "platform=x86" ]
   then
      platform="x86"
      echo "platform=x86"
      elif [ $1 == "platform=sparc" ]
      then
           platform="sparc"
      echo "platform=sparc"
      else
          platform="linux"
          echo "platform=linux"
   fi
else
     echo
     echo "Invalid platform selected, please follow the below syntax."
     echo "Syntax: ./build.sh platform=[x86/sparc/linux] "
     echo
     exit 1
fi

tlsflg="no"
if [ $platform = 'sparc' ]
then
       cp AcceleroCore/config.vars.sol.gcc AcceleroCore/config.vars
       cp imsdia/make.dirs.sol.gcc imsdia/make.dirs
elif [ $platform = 'x86' ]
then
       cp AcceleroCore/config.vars.solaris AcceleroCore/config.vars
       cp imsdia/make.dirs.solCC imsdia/make.dirs
else 
       cp AcceleroCore/config.vars.linux AcceleroCore/config.vars
       cp imsdia/make.dirs.linux imsdia/make.dirs
fi
export platform tlsflg 

### Compile TLS-SNMP ###

if [ $platform = 'x86' ]
then 
### Compile AcceleroCore ###
cd $ITS_ROOT
>tlssubs
make IPV6=yes USE_STLPORT4=yes 2> ../build.log
 ### Compile IMSDIA ###
cd $IMS_ROOT
make DEBUG_BUILD=yes USE_STLPORT4=yes clean; make DEBUG_BUILD=yes USE_STLPORT4=yes 2>> ../buildD.log
make DEBUG_BUILD=no  USE_STLPORT4=yes clean; make DEBUG_BUILD=no  USE_STLPORT4=yes 2>> ../build.log

 ### OAM Compilation ###
cd $IMS_ROOT/vendors/IntelliNet/oam/subagent/src
make USE_STLPORT4=yes USE_SOL_SNMP=yes clean;
make USE_STLPORT4=yes USE_SOL_SNMP=yes 2>> $IMS_ROOT/../build.log
 
### Compile LoadSim ###

cd $IMS_ROOT/../diademo/LoadSim/Rx
make DEBUG_BUILD=no  IPV6=yes USE_STLPORT4=yes clean; make DEBUG_BUILD=no  IPV6=yes USE_STLPORT4=yes 2>> ../build.log
cd $IMS_ROOT/../diademo/LoadSim/S6a
make DEBUG_BUILD=no  IPV6=yes USE_STLPORT4=yes clean; make DEBUG_BUILD=no  IPV6=yes USE_STLPORT4=yes 2>> ../build.log

elif [ $platform = 'sparc' ]
then
### Compile AcceleroCore ###

cd $ITS_ROOT

>tlssubs

make IPV6=yes PLATFORM=solaris64 2> ../build.log

 ### Compile IMSDIA ###
cd $IMS_ROOT

make DEBUG_BUILD=yes PLATFORM=solaris64  clean; make DEBUG_BUILD=yes PLATFORM=solaris64 2>> ../buildD.log
make DEBUG_BUILD=no PLATFORM=solaris64 clean; make DEBUG_BUILD=no PLATFORM=solaris64  2>> ../build.log

 ### OAM Compilation ###
cd $IMS_ROOT/vendors/IntelliNet/oam/subagent/src
make IPV6=yes PLATFORM=solaris64 USE_SOL_SNMP=yes clean;
make IPV6=yes PLATFORM=solaris64 USE_SOL_SNMP=yes 2>> $IMS_ROOT/../build.log

### Compile LoadSim ###
cd $IMS_ROOT/../diademo/LoadSim/Rx
make DEBUG_BUILD=no  IPV6=yes PLATFORM=solaris64 clean; make DEBUG_BUILD=no  IPV6=yes PLATFORM=solaris64 2>> ../build.log
cd $IMS_ROOT/../diademo/LoadSim/S6a
make DEBUG_BUILD=no  IPV6=yes PLATFORM=solaris64 clean; make DEBUG_BUILD=no  IPV6=yes PLATFORM=solaris64 2>> ../build.log

else 
### Compile AcceleroCore ###

cd $ITS_ROOT

>tlssubs

make clean; make 2> ../build.log

 ### Compile IMSDIA ###
cd $IMS_ROOT

make DEBUG_BUILD=yes clean; make DEBUG_BUILD=yes 2>> ../buildD.log
make DEBUG_BUILD=no clean; make DEBUG_BUILD=no 2>> ../build.log

 ### OAM Compilation ###
cd $IMS_ROOT/vendors/IntelliNet/oam/subagent/src
make USE_GNU_SNMP=yes clean;
make USE_GNU_SNMP=yes 2>> $IMS_ROOT/../build.log

### Compile LoadSim ###
cd $IMS_ROOT/../diademo/LoadSim/Rx
make DEBUG_BUILD=no  clean; make DEBUG_BUILD=no  2>> ../build.log
cd $IMS_ROOT/../diademo/LoadSim/S6a
make DEBUG_BUILD=no  clean; make DEBUG_BUILD=no  2>> ../build.log

fi

echo " Build Over"
