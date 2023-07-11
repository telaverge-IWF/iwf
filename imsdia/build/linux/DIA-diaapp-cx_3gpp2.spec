%define pkg CX-3GPP2
%define BASEDIR /opt/IntelliNet
%define BACKUPDIR /opt/IntelliNet/IMS-CX-3GPP2_BKP
%define RELDIR /tmp/RPM_cx_3gpp2
%define VERSION 2.1
%define OLDVERSION 2.0
%define user intelli
%define group other 
%define name CX-3GPP2 

Summary: IMS Diameter Server Software
Name: %name
Version: %VERSION 
Release: 2 
License: IntelliNet Technologies
Group: Applications
URL: http://www.intellinet-tech.com
Vendor: IntelliNet
Packager:Vijikumar N
BuildRoot: %RELDIR
Prefix: /opt/IntelliNet

%description
IntelliNet Technologies, IMS Diameter Server Software

# List of files.
%files
/opt/IntelliNet

# Pre-Install script
%pre
PKG=%pkg
BASEDIR=%BASEDIR/CX-3GPP2-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
USER=%user
GROUP=%user

echo "Checking for base Package installation... "
echo " "
ls /opt/IntelliNet/ | grep IMSDIA-GA- > /dev/null
pkgBase=`echo $?`
ls /opt/IntelliNet/ | grep IDC- > /dev/null
pkgDist=`echo $?`
if [ $pkgBase -eq 0 ]
then
    echo ""
elif [ $pkgDist -eq 0 ]
then
    echo ""
else
    echo "Pls first install Base Packages and then install $PKG"
    echo " "
    exit 1
fi

#
# Check if installing user is not root
#
if [ `id -u` != 0 ]
then
    echo ""
    echo "*** ERROR: Only root user can install this package."
    echo "For more information, consult the installation manual."
    echo ""
    exit 3
fi
#
# Check if hostid 0x7f0100(localhost)
#
if [ `hostid` = "7f0100" ]
then
    echo ""
    echo "*** ERROR:"
    echo "Please set the hostname and IP address of the machine"
    echo "else"
    echo "Set the hostid in the /etc/hostid file"
    exit 3
fi 

# 
# Post Install script
#
%post
BASEDIR=%BASEDIR/CX-3GPP2-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
USER=%user
GROUP=%user
echo "cx_3gpp2 Post Installation..."

if [ `id $USER | cut -d "(" -f3 | cut -d ")" -f1` != "$GROUP" ]
then
    groupadd $GROUP
fi
chown -Rh $USER:$GROUP $BASEDIR

# Check to see if there was a previous version
# of Package installed & it's configuration was
# backed up. If it was copy the license file,
# & configuration files.
if [ -d $BACKUPDIR ]
then
    for dir in `ls -1 $BACKUPDIR`
    do
        if [ -f $BACKUPDIR/$dir/config/its.lic ]
        then
           echo "Copying license file from backed up configuration"
           cp $BACKUPDIR/$dir/config/its.lic $BASEDIR/config
           echo "DONE"
           exit 0
        fi
    done
fi

# Pre Remove Script
%preun
BASEDIR=%BASEDIR/CX-3GPP2-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
echo "CX-3GPP2 Pre Removal..."
if [ -d $BASEDIR/config  ]
then
    echo ""
    echo " Backing up $BASEDIR as $BACKUPDIR/CX-3GPP2-%VERSION"
    if [ ! -d $BACKUPDIR ]
    then
       mkdir -p $BACKUPDIR
    fi

    if [ -d $BACKUPDIR/CX-3GPP2-%VERSION ]
    then
       # Remove the same version backup
       /bin/rm -rf $BACKUPDIR/CX-3GPP2-%VERSION
    fi

    cp -r $BASEDIR $BACKUPDIR
    if [ $? -eq 0 ]
    then
         echo " Backup complete "
    fi
    echo ""
fi

# Post Remove Script
%postun
BASEDIR=%BASEDIR/CX-3GPP2-%VERSION
USER=%user
VERSION=%VERSION
OLDVERSION=%OLDVERSION
echo "cx_3gpp2 Post Removal..."

#
# Bring the system back to as it was before installation
#
if [ -d $BASEDIR  ]
then
    echo ""
    echo "Removing $BASEDIR directory "
    rm -rf $BASEDIR
    if [ $? -eq 0 ]
    then
         echo "DONE"
    fi
    echo ""
fi
