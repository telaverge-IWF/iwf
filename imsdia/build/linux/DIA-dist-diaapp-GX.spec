%define pkg IDC
%define BASEDIR /opt/IntelliNet
%define BACKUPDIR /opt/IntelliNet/IDC-GX_BKP
%define RELDIR /tmp/RPM_IDC
%define VERSION 1.2
%define OLDVERSION 1.1
%define user intelli
%define group other
%define name IDC-GX

Summary: IMS Diameter Server Software
Name: %name
Version: %VERSION
Release: 0
License: Intellinet Technologies
Group: Applications
URL: http://www.intellinet-tech.com
Vendor: Intellinet
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
VERSION=%VERSION
PKG=%pkg
BASEDIR=%BASEDIR/IDC-%VERSION
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
%post
VERSION=%VERSION
BASEDIR=%BASEDIR/IDC-%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
USER=%user
GROUP=%user
echo "IDC-GX Post Installation..."

chown -Rh $USER:$GROUP $BASEDIR

# Check to see if there was a previous version
# of Package installed & it's configuration was
# backed up. If it was copy the license file,

# Pre Remove Script
%preun
VERSION=%VERSION
BASEDIR=%BASEDIR/IDC-%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
echo "IDC-GX Pre Removal..."
if [ -d $BASEDIR/config  ]
then
    echo ""
    echo " Backing up $BASEDIR as $BACKUPDIR/IDC-$VERSION"
    if [ ! -d $BACKUPDIR/IDC-APPS-%VERSION ]
    then
       mkdir -p $BACKUPDIR/IDC-APPS-%VERSION
    fi

    if [ -d $BACKUPDIR/IDC-APPS-$VERSION ]
    then
       # Remove the same version backup
       /bin/rm -rf $BACKUPDIR/IDC-APPS-$VERSION
    fi
    cp -pr $BASEDIR $BACKUPDIR/IDC-APPS-$VERSION
    if [ $? -eq 0 ]
    then
         echo " Backup complete "
    fi
    echo ""
fi

# Post Remove Script
%postun
VERSION=%VERSION
BASEDIR=%BASEDIR/IDC-%VERSION
OLDVERSION=%OLDVERSION
USER=%user
echo "IDC-GX Post Removal..."

#
# Bring the system back to as it was before installation
#
if [ -d $BASEDIR ]
then
    echo ""
fi
