#!/bin/bash
PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh


LOCAL_IP=`GetMysqlLocalIP`
LOCAL_HOSTNAME=`GetMysqlLocalHostname`
MATE_IP=`GetMysqlMateIP`
MATE_HOSTNAME=`GetMysqlMateHostname`
MODE=`GetHAMode`
VIRTUAL_CIDR=`GetVirtualIP`
VIRTUAL=`echo "$VIRTUAL_CIDR"|cut -d'/' -f1`
ETHE=`GetEthernet`
NETWORK_ADD=`GetBroadcastAddress`
SUBNET=`GetSubNetMaskPrefixLen`
AUTO_FAILBACK="off"
DEBUG="1"

ps -elf | grep heartbeat | grep -v grep | grep master  >/dev/null
if [ $? -eq 0 ];then
    kill_heartbeat &
    /etc/init.d/heartbeat stop
fi



cp -f $ISS7_CONFIG_DIR/heartbeat/authkeys /etc/ha.d/.

grep "^auth 1" /etc/ha.d/authkeys >/dev/null
if [ $? -ne 0 ];then
    sed -i "s/^#auth .*/auth 1/g" /etc/ha.d/authkeys

fi


grep "^1 crc" /etc/ha.d/authkeys >/dev/null
if [ $? -ne 0 ];then
	sed -i "s/^#1 crc */1 crc/g" /etc/ha.d/authkeys
fi

cp -f $ISS7_CONFIG_DIR/heartbeat/haresources /etc/ha.d/.

grep "$LOCAL_HOSTNAME" /etc/ha.d/haresources

if [ $? -ne 0 ]; then
    if [ "$MODE" == "SLAVE" ];then
	    echo "$MATE_HOSTNAME IPaddr::$VIRTUAL/$SUBNET/$ETHE/$NETWORK_ADD" >> /etc/ha.d/haresources
    else
	    echo "$LOCAL_HOSTNAME IPaddr::$VIRTUAL/$SUBNET/$ETHE/$NETWORK_ADD" >> /etc/ha.d/haresources
    fi
fi

cp -f $ISS7_CONFIG_DIR/heartbeat/ha.cf /etc/ha.d/.

chmod 600 /etc/ha.d/ha.cf
chmod 600 /etc/ha.d/haresources
chmod 600 /etc/ha.d/authkeys


grep "^debug*" /etc/ha.d/ha.cf >/dev/null
if [ $? -ne 0 ];then
    if [ "$DEBUG" == "1" ]; then
        if [ -z "$HA_CONF" ]; then
	    sed -i "s/^#debug.*/debug 1/g" /etc/ha.d/ha.cf
        fi
    else
        if [ -z "$HA_CONF" ]; then
	    sed -i "s/^#debug.*/debug 0/g" /etc/ha.d/ha.cf
        fi
    fi
fi

echo "node $LOCAL_HOSTNAME" >> /etc/ha.d/ha.cf
echo "node $MATE_HOSTNAME" >> /etc/ha.d/ha.cf

sed -i "s/auto_failback.*/auto_failback $AUTO_FAILBACK/g" /etc/ha.d/ha.cf

echo "ucast $ETHE $MATE_IP" >> /etc/ha.d/ha.cf

echo "baud  19200" >> /etc/ha.d/ha.cf
echo "udpport 694" >> /etc/ha.d/ha.cf
echo "deadtime 5" >> /etc/ha.d/ha.cf
echo "keepalive 1" >> /etc/ha.d/ha.cf
echo "logfacility     local0" >> /etc/ha.d/ha.cf
echo "logfile /var/log/ha-log" >> /etc/ha.d/ha.cf
echo "debugfile /var/log/ha-debug" >> /etc/ha.d/ha.cf


grep "iptables --flush" /etc/rc.d/rc.local > /dev/null
if [ $? -ne 0 ];then
    echo "iptables --flush" >> /etc/rc.d/rc.local
fi

touch /etc/hosts

if [ "`cat /etc/hosts | wc -l`" == "0" ];then
	echo "#### >>>>> #####" >> /etc/hosts
fi

sed -i /"^$LOCAL_IP.*"/d  /etc/hosts
sed -i "1s/^/$LOCAL_IP $LOCAL_HOSTNAME\n/" /etc/hosts

sed -i /"^$MATE_IP.*"/d  /etc/hosts
sed -i "1s/^/$MATE_IP $MATE_HOSTNAME\n/" /etc/hosts

service network restart
/etc/init.d/heartbeat start
pgrep "heartbeat" >/dev/null
if [ $? -ne 0 ];then
    exit 1
fi
