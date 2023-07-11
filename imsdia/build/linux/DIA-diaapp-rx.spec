%define pkg RX
%define BASEDIR /opt/IntelliNet
%define BACKUPDIR /opt/IntelliNet/IMS-RX_BKP
%define RELDIR /tmp/RPM_rx
%define VERSION 2.1
%define OLDVERSION 2.0
%define user intelli
%define group other 
%define name RX 

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
BASEDIR=%BASEDIR/RX-%VERSION
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
# Check if package is already installed
# $PKG is set by the pkgadd utility.
#echo "Checking for pre-existing installation... "
#rpm -qa | grep $PKG
#if [ $? -eq 0 ]
#then
#    echo ""
#    echo "*** ERROR: Another instance of $PKG exists."
#    echo "Remove old package using:"
#    echo "  rpm -e $PKG"
#    echo "For more information, consult the installation manual."
#    echo ""
#    exit 3
#fi
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
BASEDIR=%BASEDIR/RX-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
USER=%user
GROUP=%user
echo "rx Post Installation..."

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
BASEDIR=%BASEDIR/RX-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
echo "RX Pre Removal..."
if [ -d $BASEDIR/config  ]
then
    echo ""
    echo " Backing up $BASEDIR as $BACKUPDIR/RX-%VERSION"
    if [ ! -d $BACKUPDIR ]
    then
       mkdir -p $BACKUPDIR
    fi

    if [ -d $BACKUPDIR/RX-%VERSION ]
    then
       # Remove the same version backup
       /bin/rm -rf $BACKUPDIR/RX-%VERSION
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
BASEDIR=%BASEDIR/RX-%VERSION
USER=%user
VERSION=%VERSION
OLDVERSION=%OLDVERSION
echo "rx Post Removal..."

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
