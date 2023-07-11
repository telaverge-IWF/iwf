#!/bin/bash

if [ -z $1 ]
then
   echo
   echo "Invalid operating system entry, please follow the below syntax."
   echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]"
   echo
   exit 1
elif [ $1 == "os=linux" -o $1 == "os=solaris" ]
then
     if [ $1 = "os=linux" ]
     then
        OS=linux
     else
        OS=solaris
     fi
else
     echo
     echo "Invalid operating system selected, please follow the below syntax."
     echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]" 
     echo
     exit 1
fi

if [ -z $2 ]
then
   echo
   echo "Invalid platform entry, please follow the below syntax."
   echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]"
   echo
   exit 1
elif [ $2 == "platform=x86" -o $2 == "platform=pp50" ]
then
   if [ $2 == "platform=x86" ]
   then
      platform="x86"
   else
      platform="pp50"
   fi
else
     echo
     echo "Invalid platform selected, please follow the below syntax."
     echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]" 
     echo
     exit 1
fi

if [ -z $3 ]
then
   tlsflg=no
elif [ $3 == "tls=yes" -o $3 == "tls=no" ]
then
     if [ $3 = "tls=yes" ]
     then
        tlsflg="yes"
     else
        tlsflg="no"
     fi
else
     echo
     echo "Invalid TLS option selected, please follow the below syntax."
     echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]"
     echo
     exit 1
fi

if [ $2 = "platform=pp50" ]
then
if [ -z $4 ]
then
   echo "Invalid SDK entry, please follow the below syntax."
   echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]"
   echo
   exit 1
elif [ $4 == "sdk=rmi" -o $4 == "sdk=windriver" ]
then
   if [ $4 = "sdk=rmi" ]
   then
     SDK="rmi"
   else
     SDK="windriver"
   fi
fi
fi

if [ $platform = "pp50" -a $OS = "solaris" ]
then
   echo 
   echo "Miss match platform and operating system selected"
   echo
   exit 0
fi

if [ $platform = 'pp50' ]
then
   if [ $4 = 'sdk=rmi' ]
   then
       cp AcceleroCore/config.vars.rmi AcceleroCore/config.vars
       cp imsdia/make.dirs.rmi imsdia/make.dirs
   elif [ $4 = 'sdk=windriver' ]
   then
       cp AcceleroCore/config.vars.wr AcceleroCore/config.vars
       cp imsdia/make.dirs.wr imsdia/make.dirs
   else
       echo "Invalid SDK option selected, please follow the below syntax."
       echo "Syntax: make os=[linux/solaris] platform=[x86/pp50] tls=[yes/no] sdk=[rmi/windriver]"
       exit 0
    fi
else
   cp AcceleroCore/config.vars.linux AcceleroCore/config.vars
   cp imsdia/make.dirs.linux imsdia/make.dirs
fi


export OS platform tlsflg SDK

### Compile TLS-SNMP ###

cd imstools
./build.sh

### Compile AcceleroCore ###

if [ $SDK = "rmi" ]
then
   if [ -f /usr/local/include/netinet/sctp.h ]
   then 
     cd $ITS_ROOT
     make 2> ../build.log
   else
     mkdir $ITS_ROOT/common/include/netinet
     cp -r $LKSCTP_ROOT/src/include/netinet/sctp.h $ITS_ROOT/common/include/netinet/
     cd $ITS_ROOT
     make 2> ../build.log
   fi
else
   cd $ITS_ROOT
   make 2> ../build.log
fi

if [ $SDK = "rmi" ]
then 
     cp $LKSCTP_ROOT/src/lib/.libs/libsctp.so $ITS_ROOT/common/lib
fi 

 ### Compile IMSDDIA ###
 cd $IMS_ROOT
 make clean 2>> ../build.log
 make 2>> ../build.log

 ### OAM Compilation ###
 cd $IMS_ROOT/vendors/IntelliNet/oam/server/src
 make 2>> $IMS_ROOT/../build.log
 cd $IMS_ROOT/vendors/IntelliNet/oam/subagent/src
 make 2>> $IMS_ROOT/../build.log

 ### TLS Compilation ###

 if [ $tlsflg = 'yes' ]
 then 
    cd $IMS_ROOT/vendors/IntelliNet/src
    make clean TLS=yes 
    make TLS=yes 2>> $IMS_ROOT/../build.log
    cd $IMS_ROOT/aim/server/src
    make clean TLS=yes
    make TLS=yes 2>> $IMS_ROOT/../build.log
    cd $IMS_ROOT/itsdemo/src
    make clean TLS=yes
    make TLS=yes 2>> $IMS_ROOT/../build.log
    cd $IMS_ROOT/../
fi
