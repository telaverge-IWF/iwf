%define pkg IDC
%define BASEDIR /opt/IntelliNet
%define BACKUPDIR /opt/IntelliNet/IDC_BKP
%define RELDIR /tmp/RPM_IDC
%define VERSION 1.2
%define OLDVERSION 1.1
%define user intelli
%define group other
%define name IDC

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
# Creating user
#
id $USER > /dev/null 2>&1

rc=$?
if [ $rc -eq 0 ]; then
   echo "OK: user $USER exists"
   echo "OK: Setting user $USER home directory to path to $BASEDIR"
   userdel $USER
   if [ ! -d $BASEDIR ]
   then
       mkdir -p $BASEDIR
   fi
   useradd -c "User intelli" -d $BASEDIR -s /bin/bash $USER
   echo "NOTE: NOTE: Please execute <passwd intelli> command "
   echo "as root and reset the password to the $USER user"
else
   echo "INSTALLATION: Creating user $USER "
   if [ ! -d $BASEDIR ]
   then
       mkdir -p $BASEDIR
   fi
   useradd -c "User intelli" -d $BASEDIR -s /bin/bash $USER
   echo ""
   echo "NOTE: NOTE: Please execute <passwd intelli> command "
   echo "as root to set the password for user $USER"
fi
   echo "INSTALLATION: Package will be installed in $BASEDIR "
   echo ""

# Post Install script
%post
VERSION=%VERSION
BASEDIR=%BASEDIR/IDC-%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
USER=%user
GROUP=%user
echo "IDC Post Installation..."

if [ -e $BASEDIR/.bash_profile ]
then
    mv $BASEDIR/.bash_profile $BASEDIR/.bash_profile.old
fi
cp $BASEDIR/config/Profile $BASEDIR/.bash_profile
if [ `id $USER | cut -d "(" -f3 | cut -d ")" -f1` != "$GROUP" ]
then
    groupadd $GROUP
fi
chown -Rh $USER:$GROUP $BASEDIR
if [ -e /usr/lib/libssl.so.4 ]
then
    echo ""
else
    ln -s /usr/lib/libssl.so /usr/lib/libssl.so.4
fi
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
VERSION=%VERSION
BASEDIR=%BASEDIR/IDC-%VERSION
OLDVERSION=%OLDVERSION
BACKUPDIR=%BACKUPDIR
echo "IDC Pre Removal..."
if [ -d $BASEDIR/config  ]
then
    echo ""
    echo " Backing up $BASEDIR as $BACKUPDIR/IDC-$VERSION"
    if [ ! -d $BACKUPDIR ]
    then
       mkdir -p $BACKUPDIR
    fi

    if [ -d $BACKUPDIR/IDC-$VERSION ]
    then
       # Remove the same version backup
       /bin/rm -rf $BACKUPDIR/IDC-$VERSION
    fi
    cp -pr $BASEDIR $BACKUPDIR
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
echo "IDC Post Removal..."

#
# Bring the system back to as it was before installation
#
if [ -d $BASEDIR ]
then
    echo ""
    echo "Removing $BASEDIR directory "
    rm -r $BASEDIR
    if [ $? -eq 0 ]
    then
         echo "DONE"
    fi
    id $USER > /dev/null 2>&1
    rc=$?
    if [ $rc -eq 0 ]; then
       if [ `finger intelli | grep Directory | awk '{ print $2}'` = "$BASEDIR" ]
       then
          userdel $USER
       fi
    fi
    echo ""
fi
