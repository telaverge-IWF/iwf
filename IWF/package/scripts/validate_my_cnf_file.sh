#!/bin/bash
#checking my.cnf
#

PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh

MYSQL_PATH="\/opt\/diametriq\/share\/mysql"
CHECK_PATH=/opt/diametriq/share/mysql/english
MYSQL_CNFPATH=/etc/my.cnf

function add_to_file()
{
	echo ""	
}

function remove_from_file()
{
	/bin/sed -i "s/^lc-messages-dir.*/#lc-messages-dir=$MYSQL_PATH/g"  $MYSQL_CNFPATH
	/bin/sed -i "s/^character-sets-dir.*/#character-sets-dir=$MYSQL_PATH\/character/g"  $MYSQL_CNFPATH
}

if [ -d $CHECK_PATH ];then
	add_to_file
else
	remove_from_file
fi

command_my_cnf_for_standalone
uncommand_my_cnf_for_activestandby
if [ $PRODUCT = "dre" ];then
    cp -f $MYSQL_CNFPATH $DRE_ROOT/.syscfg 
fi

if [ $PRODUCT = "iwf" ];then
    cp -f $MYSQL_CNFPATH $IWF_ROOT/.syscfg 
fi
