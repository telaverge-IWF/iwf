#!/bin/bash
echo "Installing incron..."
mkdir -p /usr/local/share/man/man1
mkdir -p /usr/local/share/man/man5
mkdir -p  /usr/local/share/man/man8
cp -f  incrontab.1 /usr/local/share/man/man1
cp -f  incrontab.5 /usr/local/share/man/man5
cp -f  incrond.8 /usr/local/share/man/man8
cp -f  incron.conf.5 /usr/local/share/man/man5
mkdir -p /usr/local/share/doc/incron-`cat VERSION`//
cp -f   incrontab /usr/local/bin/
cp -f   incrond /usr/local/sbin/
mkdir -p /var/spool/incron
mkdir -p /etc/incron.d
cp -f incron.conf.example /usr/local/share/doc/incron-`cat VERSION`//
echo "Incron installation successfull!"

