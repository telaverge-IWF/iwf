#!/bin/bash
##Function to compile TIPC on the target machine)
function compile_tipc()
{
    local ret=0
    local TIPC_SRC=tipc-1.7.7.tar
    #local KERNEL_SRC=/usr/src/kernels/`uname -r`/
    local KERNEL_SRC=/usr/src/kernels/3.10.0-1160.90.1.el7.x86_64
    local ROOT=`pwd`
    if [ ! -d $KERNEL_SRC ];then
	echo "$KERNEL_SRC not found!"
   	echo "Install kernel-devel-`uname -r`!"
      
    fi
    cp -f $TIPC_SRC $KERNEL_SRC
    cd $KERNEL_SRC
    tar -xvf $TIPC_SRC




    #the below command will configure the TIPC with default options without invoking make menuconfig
    ./scripts/config --module TIPC  --enable TIPC_UNICLUSTER_FRIENDLY --enable TIPC_MULTIPLE_LINKS --enable TIPC_CONFIG_SERVICE --enable TIPC_SOCKET_API --enable TIPC_SYSTEM_MSGS --disable TIPC_DEBUG --disable TIPC_ADVANCED


    make
    echo "Ignore the above errors(if any) during compilation!"

    make clean M=net/tipc

    make M=net/tipc
    if [  -e net/tipc/tipc.ko ] ;then
	ret=0
	echo "TIPC compilation success!"
    	cp -f net/tipc/tipc.ko $ROOT
    else

        ret=1
        echo "Retrying TIPC compilation with new sk_add_backlog() change.."
        mv net/tipc/tipc_socket.c net/tipc/tipc_socket_back.c
        cp net/tipc/tipc_socket_new.c net/tipc/tipc_socket.c	
        make M=net/tipc
	if [ -e net/tipc/tipc.ko ];then
	    ret=0
	    echo "TIPC compilation success!"
    	    cp -f net/tipc/tipc.ko $ROOT

        else
	    echo "TIPC Compilation Failed!"
	    ret=1
	fi

    fi
 
    rm -f $TIPC_SRC
    cd $ROOT
    return $ret
}

compile_tipc
if [ $? -eq 0 ];then
    ./install.sh --install
fi

