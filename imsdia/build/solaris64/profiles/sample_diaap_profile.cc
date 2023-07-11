#!/bin/bash
echo 'export PS1="${LOGNAME}@`uname -n`!$ "'
echo""
echo '#'
echo '# Path settings.'
echo '#'
echo 'PATH=$PATH:.'
echo 'PATH=$PATH:/bin/'
echo 'PATH=$PATH:/usr/bin'
echo 'PATH=$PATH:/usr/local/bin'
echo 'PATH=$PATH:/opt/SUNWspro/bin'
echo 'PATH=$PATH:/usr/sbin'


echo""
echo '#'
echo '# LD_LIBRARY_PATH settings.'
echo '#'
echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib'
echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/SUNWspro/lib'
echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib'
echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lib'
echo `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/apps/common/lib:../../lib`
export LD_LIBRARY_PATH
echo""
echo '#'
echo '# IMS Diameter Related'
echo '#'
echo PLATFORM=solaris
export PLATFORM

echo DEBUG_BUILD=yes
echo IMS_ROOT=/opt/IntelliNet/IMSDIA-GA-$IMS_VER
echo IMS_TOOLS=/opt/IntelliNet/IMSDIA-GA-$IMS_VER/imstools
echo ITS_ROOT=/opt/IntelliNet/IMSDIA-GA-$IMS_VER/AcceleroCore
echo ISS7_CONFIG_DIR=/opt/IntelliNet/IMSDIA-GA-$IMS_VER/config/
echo ITS_MAN_PATH=/opt/IntelliNet/IMSDIA-GA-$IMS_VER/dbchelp/

echo 'PATH=$PATH:$IMS_ROOT/demo/bin:$IMS_ROOT/scripts'

echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/lib:$IMS_ROOT/demo/lib:../../lib'

echo""
echo export PATH LD_LIBRARY_PATH PLATFORM
echo export ITS_ROOT IMS_ROOT IMS_TOOLS ITS_MAN_PATH
echo export ISS7_CONFIG_DIR
echo export DEBUG_BUILD
