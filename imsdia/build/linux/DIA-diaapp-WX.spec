%define pkg IMSDIA-GA
%define BASEDIR /opt/IntelliNet
%define BACKUPDIR /opt/IntelliNet/IMS-WX_BKP
%define RELDIR /tmp/RPM_imsdia
%define VERSION 1.2
%define OLDVERSION 1.1
%define user intelli
%define group other 
%define name WX

Summary: IMS Diameter Server Software
Name: %name
Version: %VERSION 
Release: 0 
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
BASEDIR=%BASEDIR/IMSDIA-GA-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
USER=%user
GROUP=%user

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
rpm -qa | grep $PKG
if [ $? -eq 0 ]
then
    echo ""
else
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
BASEDIR=%BASEDIR/IMSDIA-GA-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
USER=%user
GROUP=%user
echo "wx Post Installation..."

chown -Rh $USER:$GROUP $BASEDIR

# Check to see if there was a previous version
# of Package installed & it's configuration was
# backed up. If it was copy the license file,

# Pre Remove Script
%preun
BASEDIR=%BASEDIR/IMSDIA-GA-%VERSION
VERSION=%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
echo "WX Pre Removal..."
if [ -d $BASEDIR/config  ]
then
    echo ""
    echo " Backing up $BASEDIR as $BACKUPDIR/IMSDIA-GA-%VERSION"
    if [ ! -d $BACKUPDIR/APPS-GA-%VERSION ]
    then
       mkdir -p $BACKUPDIR/APPS-GA-%VERSION
    fi

    if [ -d $BACKUPDIR/APPS-GA-%VERSION ]
    then
       # Remove the same version backup
	/bin/rm -rf $BACKUPDIR/APPS-GA-%VERSION
    fi

    cp -r $BASEDIR/apps $BACKUPDIR/APPS-GA-%VERSION
    if [ $? -eq 0 ]
    then
         echo " Backup complete "
    fi
    echo ""
fi

# Post Remove Script
%postun
BASEDIR=%BASEDIR/IMSDIA-GA-%VERSION
USER=%user
VERSION=%VERSION
OLDVERSION=%OLDVERSION
echo "wx Post Removal..."

#
# Bring the system back to as it was before installation
#
if [ -d $BASEDIR  ]
then
    echo ""
     echo "Removing $BASEDIR directory "
    rm -rf $BASEDIR\apps\wx

fi
