#!/bin/bash

PRODUCT=iwf
DRE_CONFIG=/etc/${PRODUCT}.cfg
#get the tipc config parameters from the dre config file
function GetNetID()
{
    sed -n s/NetID=//p $DRE_CONFIG
}

function GetTipcNodeAddress()
{
    sed -n s/TipcNodeAddress=//p $DRE_CONFIG
}

function GetBearerName()
{
    sed -n s/BearerName=//p $DRE_CONFIG
}

if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1
fi
#if tipc is already configured remove and configure
lsmod |grep "tipc" >/dev/null
if [ $? -eq 0 ];then
    rmmod tipc
else

    echo "Copying files..."
    cp include/linux/tipc*  /usr/include/linux
    cp tipc-config /usr/sbin

    mkdir -p /lib/modules/2.6.32-220.el6.x86_64/kernel/net/tipc
    cp tipc.ko /lib/modules/2.6.32-220.el6.x86_64/kernel/net/tipc

    echo "Depmod..."
    depmod -a

    echo "Loading tipc kernel module..."
fi
modprobe tipc 2>/dev/null


if [ $? -ne 0 ]; then
    echo "Loading module failed. Check the kernel version!"
    exit 1
fi

echo "Loading module on boot"
sed -i '/^modprobe tipc/d' /etc/rc.modules 2>/dev/null
cat >>  /etc/rc.modules <<EOF
modprobe tipc
EOF
chmod +x /etc/rc.modules

net_id=$( GetNetID )
echo NetId=$net_id
node_addr=$( GetTipcNodeAddress )
echo TipcNodeAddress=$node_addr
eth_inf=$( GetBearerName )
echo "BearerName(eth_inf)=$eth_inf"
echo "Configuring TIPC"

tipc-config -netid=$net_id -a=$node_addr -be=$eth_inf
sed -i '/^tipc-config.*/d' /etc/rc.d/rc.local
cat >> /etc/rc.d/rc.local << EOF
tipc-config -netid=$net_id -a=$node_addr -be=$eth_inf
EOF

echo "Installation completed."

